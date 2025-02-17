/****************************************************************************************
* Date: 17-02-2025
* Author: Hamza Taous
* Github Username : taous97
* Github Link Library : https://github.com/hamzat97/ATmega328P_Scratch_Made_Drivers
*****************************************************************************************/

#include "TIMER1.h"
#include <avr/io.h>

void timer1_delay_ms(uint16_t delay_ms, uint16_t prescaler) {
    TCCR1A = 0x00; // Normal mode, no PWM
    // Configure Timer1 in CTC mode and set the prescaler in TCCR1B based on the given argument
    switch (prescaler) {
        case 1:
            TCCR1B = 0x09; // CTC mode, prescaler 1
            break;
        case 8:
            TCCR1B = 0x0A; // CTC mode, prescaler 8
            break;
        case 64:
            TCCR1B = 0x0B; // CTC mode, prescaler 64
            break;
        case 256:
            TCCR1B = 0x0C; // CTC mode, prescaler 256
            break;
        case 1024:
            TCCR1B = 0x0D; // CTC mode, prescaler 1024
            break;
        default:
            // Default to prescaler 64 if an unsupported prescaler is passed
            TCCR1B = 0x0B; // CTC mode, prescaler 64
            prescaler = 64; // Adjust the prescaler for the compare match value calculation 
            break;
    }
    
    // Calculate the compare match value for 1ms delay
    // Formula: OCR1A = (F_CPU / (2 * Prescaler * Frequency)) - 1
    OCR1A = (uint16_t)((F_CPU / prescaler / 1000) - 1); // For 1 ms delay with 16 MHz clock

    // Loop for the required number of milliseconds
    for (uint16_t i = 0; i < delay_ms; i++) {
        TCNT1 = 0; // Reset counter
        TIFR1 |= (1 << OCF1A); // Clear compare match flag
        
        // Wait for the compare match flag to be set
        while (!(TIFR1 & (1 << OCF1A)));
    }
}

// Function to to count falling edges on T1 pin using Timer1
void timer1_count_events(uint16_t target_count, uint8_t edge_type) {
    TCCR1A = 0x00; // Normal port operation, no PWM
    // Configure Timer1 in CTC mode and select the edge type on T1 (PD5) based on the given argument
    if (edge_type == 0) { // Falling edge
        TCCR1B = 0x0E; // CTC mode, external clock on falling edge
    } else if (edge_type == 1) { // Rising edge
        TCCR1B = 0x0F; // CTC mode, external clock on rising edge
    } else {
        // Invalid edge type, set to default (falling edge)
        TCCR1B = 0x0E;
    }

    // Set the compare match register (OCR1A) to the target count
    OCR1A = target_count; // 16-bit access to OCR1A

    // Reset Timer1 counter register
    TCNT1 = 1; // 16-bit access to TCNT1

    // Wait until the target count is reached
    while (!(TIFR1 & (1 << OCF1A)));

    // Toggle the output pin in PORTB (PB5) when the count is reached
    PORTB ^= (1 << PB5);

    // Clear the output compare match flag by writing a logic one
    TIFR1 |= (1 << OCF1A);
}

void timer1_pwm_generation(uint8_t duty_cycle1, uint8_t duty_cycle2, uint16_t prescaler, uint16_t frequency, uint8_t use_two_pins, uint8_t mode, uint8_t toggle) {
    // Validate duty cycle range (0 - 100)
    if (duty_cycle1 > 100) duty_cycle1 = 100;
    if (duty_cycle2 > 100) duty_cycle2 = 100;

    // Validate use_two_pins (0 or 1)
    if (use_two_pins > 1) use_two_pins = 1;

    // Validate mode (1 = Non-inverting, 2 = Inverting)
    if (mode < 1 || mode > 2) mode = 1;
    
    // Set PB1 (OC1A) as output; if using two pins, also set PB2 (OC1B) as output
    DDRB |= (1 << DDB1);
    if (use_two_pins) {
        DDRB |= (1 << DDB2);
    }

    // Calculate the 16-bit value for ICR1 based on frequency, prescaler, and f_CPU
    uint16_t top_value = (uint16_t)((F_CPU / (prescaler * frequency)) - 1);

    // Adjust prescaler and/or frequency if top_value exceeds the max limit
    while (top_value > 65535) {
        if (prescaler == 1024) {
            frequency *= 2; // Adjust frequency to reduce top_value
            top_value = (uint16_t)((F_CPU / (prescaler * frequency)) - 1);
        } else {
            // Try next higher prescaler value
            if (prescaler == 1) prescaler = 8;
            else if (prescaler == 8) prescaler = 64;
            else if (prescaler == 64) prescaler = 256;
            else if (prescaler == 256) prescaler = 1024;

            // Recalculate top_value with new prescaler
            top_value = (uint16_t)((F_CPU / (prescaler * frequency)) - 1);
        }
    }

    // Set ICR1 to define the PWM frequency
    ICR1 = top_value;

    // Calculate the 16 bit hex value for the duty cycle and set OCR1A and OCR1B registers
    uint16_t dutyValue1 = (uint16_t)((duty_cycle1 / 100.0) * 0xFFFF); // Convert percentage1 to HEX
    uint16_t dutyValue2 = (uint16_t)((duty_cycle2 / 100.0) * 0xFFFF); // Convert percentage2 to HEX

    OCR1A = dutyValue1; // Set duty cycle for OC1A
    OCR1B = dutyValue2; // Set duty cycle for OC1B if both pins used

    // Set compare output mode based on mode parameter
    if (mode == 1) {
        // Non inverting mode for one or both outputs
        TCCR1A |= (1 << COM1A1);
        if (use_two_pins) {
            TCCR1A |= (1 << COM1B1);
        }
    } else if (mode == 2) {
        // Inverting mode for one or both outputs
        TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
        if (use_two_pins) {
            TCCR1A |= (1 << COM1B1) | (1 << COM1B0);
        }
    }

    // Set toggle behavior based on the toggle_outputs parameter
    if (toggle) {
        // Configure for toggle mode
        TCCR1A |= (1 << COM1A1) | (1 << COM1A0); // Inverting mode for OC1A
        if (use_two_pins) {
            TCCR1A |= (1 << COM1B1); // Non-inverting mode for OC1B
        }
    }

    // Set Fast PWM mode using ICR1 as TOP
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS12) | (1 << CS10);

    // Apply the chosen prescaler
    switch (prescaler) {
        case 1:
            TCCR1B |= (1 << CS10); // Prescaler 1
            break;
        case 8:
            TCCR1B |= (1 << CS11); // Prescaler 8
            break;
        case 64:
            TCCR1B |= (1 << CS11) | (1 << CS10); // Prescaler 64
            break;
        case 256:
            TCCR1B |= (1 << CS12); // Prescaler 256
            break;
        case 1024:
            TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
            break;
        default:
            TCCR1B |= (1 << CS12) | (1 << CS10); // Default prescaler 1024
            break;
    }

    // Infinite loop to maintain PWM
    while (1); {}
}
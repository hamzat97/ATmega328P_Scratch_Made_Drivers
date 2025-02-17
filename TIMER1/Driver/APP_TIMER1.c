#include "TIMER1.h"
#include <avr/io.h>

uint8_t ModeSwich = 3;
uint16_t delay_ms = 3000;
uint16_t prescaler_for_delay_ms = 64;
uint16_t target_count = 5;
uint8_t edge_type_count = 0;
uint8_t duty_cycle1 = 50;
uint8_t duty_cycle2 = 50;
uint16_t prescaler_for_PWM = 1024;
uint16_t frequency_for_PWM = 0.5;
uint8_t two_pins_for_PWM = 1;
uint8_t output_mode_for_PWM = 1;
uint8_t toggle_for_PWM = 1;

int main(void) {
    if (ModeSwich == 1) {
    DDRB |= (1 << PB5); // Set PORTB5 as OUTPUT
    
    while (1) {
        PORTB |= (1 << PB5);  // Set PORTB5 HIGH
        timer1_delay_ms(delay_ms, prescaler_for_delay_ms); // Wait for 500 ms
        PORTB &= ~(1 << PB5); // Set PORTB5 LOW
        timer1_delay_ms(delay_ms, prescaler_for_delay_ms); // Wait for 500 ms
    }
    }
    
    else if (ModeSwich == 2) {
    // Set PB5 as output for LED control
    DDRB |= (1 << PB5);
    PORTB &= ~(1 << PB5); // Ensure the LED is initially off

    // Set PB1 as input to count external events (button presses)
    DDRB &= ~(1 << PB1); // Set PB1 as input
    PORTB |= (1 << PB1); // Enable pull-up resistor on PB1

    // Specify the target count for the function
    uint16_t target_count = 5; // Example: LED turns on after 10 button presses

    while (1) {
        // Call the counting function with the specified target
        timer1_count_events(target_count, edge_type_count);
    }
    }
    
    else {
    // Initialize PWM with the desired duty cycle and long period
    timer1_pwm_generation(duty_cycle1, duty_cycle2, prescaler_for_PWM, frequency_for_PWM, two_pins_for_PWM, output_mode_for_PWM, toggle_for_PWM);
    }
}
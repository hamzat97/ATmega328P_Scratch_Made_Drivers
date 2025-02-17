/****************************************************************************************
* Date: 17-02-2025
* Author: Hamza Taous
* Github Username : taous97
* Github Link Library : https://github.com/hamzat97/ATmega328P_Scratch_Made_Drivers
*****************************************************************************************/

#include "UART.h"
#include <avr/io.h>

#define BAUD_PRESCALE(baud) ((F_CPU / (16UL * baud)) - 1) // Calculate the baud prescale value from the desired baud rate

void UART_Init(uint16_t baud_rate, UART_DATABITS data_bits, UART_PARITY parity, UART_STOPBIT stop_bit) {
    // Set baud rate
    uint16_t ubrr_value = BAUD_PRESCALE(baud_rate);
    UBRR0H = (ubrr_value >> 8);
    UBRR0L = ubrr_value;

    // Enable transmitter and receiver
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // Set frame format: data bits, parity, and stop bits
    UCSR0C = data_bits | parity | stop_bit;
}

uint8_t UART_Available(void) {
    // Check if data is available in the receive buffer
    return (UCSR0A & (1 << RXC0)) ? 1 : 0;
}

uint8_t UART_Read(void) {
    // Wait until data is received
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void UART_Write(uint8_t data) {
    // Wait until the transmit buffer is empty
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void UART_Print(const char *str) {
    // Loop through each character in the string and send it via UART
    while (*str) {
        UART_Write(*str++);
    }
}

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
    OCR1A = (uint16_t)((F_CPU / prescaler / 1000) - 1); // For 1ms delay with 16 MHz clock

    // Loop for the required number of milliseconds
    for (uint16_t i = 0; i < delay_ms; i++) {
        TCNT1 = 0; // Reset counter
        TIFR1 |= (1 << OCF1A); // Clear compare match flag
        
        // Wait for the compare match flag to be set
        while (!(TIFR1 & (1 << OCF1A)));
    }
}
#include "UART.h"
#include <avr/io.h>

uint16_t delay_ms = 300; // 300ms delay
uint16_t prescaler_for_delay_ms = 64; // Timer1 prescaler

int main(void) {
    DDRB = 0xFF; // Set PORTD as output
    UART_Init(9600, UART_DATABITS_8, UART_PARITY_NONE, UART_STOPBIT_1); // Initialize UART with 9600 baud, 8 data bits, no parity, 1 stop bit

    while (1) {
        // Check if data is received
        if (UART_Available()) {
            uint8_t received_data = UART_Read();  // Read the received byte
            PORTB = received_data;  // Output received byte to LEDs
            UART_Print("Next"); // Send "Next" back to the transmitter
            timer1_delay_ms(delay_ms, prescaler_for_delay_ms); // Wait for 300ms
        }
    }

    return 0;
}
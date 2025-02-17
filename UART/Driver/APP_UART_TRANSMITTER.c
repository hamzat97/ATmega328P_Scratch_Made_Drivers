#include "UART.h"
#include <avr/io.h>
#include <stdlib.h>

#define RANDOM_BYTE (rand() & 0xFF) // Generate a random 8-bit byte

int is_response_next(const char *response) {
    const char target[] = "Next";
    for (uint8_t i = 0; i < 4; i++) {
        if (response[i] != target[i]) {
            return 0; // Not equal
        }
    }
    return 1; // Equal
}

int main(void) {
    DDRB |= (1 << PORTB5); // Configure PORTB5 as OUTPUT
    PORTB &= ~(1 << PORTB5); // Set PORTB5 to LOW
    UART_Init(9600, UART_DATABITS_8, UART_PARITY_NONE, UART_STOPBIT_1); // Initialize UART with 9600 baud, 8 data bits, no parity, 1 stop bit

    while (1) {
        // Generate and send a random byte
        uint8_t random_byte = RANDOM_BYTE;
        UART_Write(random_byte);

        // Wait for the receiver to send "Next"
        while (!UART_Available());
        uint8_t response[4] = {0};
        for (uint8_t i = 0; i < 4; i++) {
            response[i] = UART_Read();
        }

        // Check if the response is "Next"
        if (is_response_next(response)) {
            PORTB ^= (1 << PORTB5); // Toggle the LED state
        }
    }

    return 0;
}
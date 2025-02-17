/****************************************************************************************
* Date: 17-02-2025
* Author: Hamza Taous
* Github Username : taous97
* Github Link Library : https://github.com/hamzat97/ATmega328P_Scratch_Made_Drivers
*****************************************************************************************/

#include "GPIO.h"

// Configure GPIO pin as INPUT or OUTPUT
void GPIO_CONFIG(uint8_t port, uint8_t pin, uint8_t direction) {
    volatile uint8_t* ddr;
    
    switch (port) {
        case 'B':
            ddr = &DDRB_REG;
            break;
        case 'C':
            ddr = &DDRC_REG;
            break;
        case 'D':
            ddr = &DDRD_REG;
            break;
        default:
            return;
    }

    if (direction == OUTPUT) {
        *ddr |= (1 << pin); // Set as OUTPUT
    } else {
        *ddr &= ~(1 << pin); // Set as INPUT
    }
}

// Write value (0 or 1) to GPIO pin
void GPIO_WRITE(uint8_t port, uint8_t pin, uint8_t state) {
    volatile uint8_t* port_reg;

    switch (port) {
        case 'B':
            port_reg = &PORTB_REG;
            break;
        case 'C':
            port_reg = &PORTC_REG;
            break;
        case 'D':
            port_reg = &PORTD_REG;
            break;
        default:
            return;
    }

    if (state == HIGH) {
        *port_reg |= (1 << pin); // Set pin HIGH
    } else {
        *port_reg &= ~(1 << pin); // Set pin LOW
    }
}

// Read GPIO pin state (LOW or HIGH)
uint8_t GPIO_READ(uint8_t port, uint8_t pin) {
    volatile uint8_t* pin_reg;

    switch (port) {
        case 'B':
            pin_reg = &PINB_REG;
            break;
        case 'C':
            pin_reg = &PINC_REG;
            break;
        case 'D':
            pin_reg = &PIND_REG;
            break;
        default:
            return LOW;
    }

    return (*pin_reg & (1 << pin)) ? HIGH : LOW; // Return the bit value (HIGH or LOW)
}
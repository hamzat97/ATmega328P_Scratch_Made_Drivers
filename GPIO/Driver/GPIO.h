#ifndef GPIO_HEADER
#define GPIO_HEADER

#include <stdint.h>

#define PORTB_REG (*((volatile uint8_t*) 0x25))
#define DDRB_REG  (*((volatile uint8_t*) 0x24))
#define PINB_REG  (*((volatile uint8_t*) 0x23))
#define PORTC_REG (*((volatile uint8_t*) 0x28))
#define DDRC_REG  (*((volatile uint8_t*) 0x27))
#define PINC_REG  (*((volatile uint8_t*) 0x26))
#define PORTD_REG (*((volatile uint8_t*) 0x2B))
#define DDRD_REG  (*((volatile uint8_t*) 0x2A))
#define PIND_REG  (*((volatile uint8_t*) 0x29))
#define INPUT  0
#define OUTPUT 1
#define LOW  0
#define HIGH 1

void GPIO_CONFIG(uint8_t port, uint8_t pin, uint8_t direction); // Function to configure the direction of a GPIO pin (INPUT or OUTPUT)
void GPIO_WRITE(uint8_t port, uint8_t pin, uint8_t state); // Function to set the state of a GPIO pin (HIGH or LOW)
uint8_t GPIO_READ(uint8_t port, uint8_t pin); // Function to read the state of a GPIO pin (HIGH or LOW)

#endif
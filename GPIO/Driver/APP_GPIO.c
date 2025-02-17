#include "GPIO.h"

#define BUTTON 6
#define LED 1

int main(void) {
    GPIO_CONFIG('B', LED, OUTPUT); // Configure PORTB1 as OUTPUT
    GPIO_CONFIG('B', BUTTON, INPUT); // Configure PORTB6 as INPUT

    while (1) {
        // Read the digital value on PORTB6
        uint8_t potValue = GPIO_READ('B', BUTTON);

        // If the input state on PORTB6 is HIGH, set PORTB1 HIGH, else set PORTB1 LOW
        if (potValue == HIGH) {
            GPIO_WRITE('B', LED, HIGH); // Set PORTB1 HIGH
        } else {
            GPIO_WRITE('B', LED, LOW); // Set PORTB1 HIGH
        }
    }
    return 0;
}
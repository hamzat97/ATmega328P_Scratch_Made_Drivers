#include "ADC.h"
#include <avr/io.h>

#define POT_CHANNEL 5

int main(void) {
    uint16_t adc_value;
    uint8_t lower_8_bits;
    uint8_t upper_2_bits;

    // Initialize ADC
    ADC_init();

    // Configure PORTB as output and first two pins of PORTC as output
    DDRB = 0xFF; // Set all PORTB pins as outputs
    DDRC |= 0x03; // Set PC0 and PC1 as outputs

    while (1) {
        // Read the analog value from the potentiometer
        adc_value = ADC_read(POT_CHANNEL);
        
        // Split the ADC value into lower 8 bits and upper 2 bits
        lower_8_bits = adc_value & 0xFF;
        upper_2_bits = (adc_value >> 8) & 0x03;
        
        // Write lower 8 bits to PORTB
        PORTB = lower_8_bits;
        
        // Write upper 2 bits to first two pins of PORTC
        PORTC = (PORTC & 0xFC) | upper_2_bits;
    }

    return 0;
}
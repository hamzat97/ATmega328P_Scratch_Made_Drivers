/****************************************************************************************
* Date: 17-02-2025
* Author: Hamza Taous
* Github Username : taous97
* Github Link Library : https://github.com/hamzat97/ATmega328P_Scratch_Made_Drivers
*****************************************************************************************/

#include "ADC.h"

void ADC_init(void) {
    // Set AVcc as reference voltage and select ADC0 as input channel
    ADMUX = (1 << REFS0);

    // Set prescaler to 64 (for 16 MHz clock, results in 250 kHz ADC clock)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
    
    // Set ADCSRB to 0 for single conversion mode (default)
    ADCSRB = 0x00; // Ensure free running mode is disabled
}

uint16_t ADC_read(uint8_t channel) {
    if (channel > 7) {
        return 0; // Invalid channel
    }

    // Select ADC channel (0-7)
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);

    // Start the conversion
    ADCSRA |= (1 << ADSC);
    
    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));

    // Read ADCL first, then ADCH, and combine the result
    uint16_t result = ADCL;
    result |= (ADCH << 8); // Combine low and high byte

    return result;
}
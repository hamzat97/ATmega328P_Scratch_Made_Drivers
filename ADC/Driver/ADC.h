#ifndef ADC_HEADER
#define ADC_HEADER

#include <avr/io.h>

#define CHANNEL_0 0
#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_3 3
#define CHANNEL_4 4
#define CHANNEL_5 5
#define CHANNEL_6 6
#define CHANNEL_7 7

void ADC_init(void); // Function to initialize the ADC
uint16_t ADC_read(uint8_t channel); // Function to read the analog value from a specified ADC channel

#endif
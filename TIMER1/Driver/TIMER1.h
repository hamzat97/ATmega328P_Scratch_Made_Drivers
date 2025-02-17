#ifndef TIMER1_HEADER
#define TIMER1_HEADER

#include <stdint.h>

void timer1_delay_ms(uint16_t delay_ms, uint16_t prescaler); // Function to generate a delay in milliseconds using Timer1 in CTC Mode
void timer1_count_events(uint16_t target_count, uint8_t edge_type); // Function to count external clock events on T1 pin using Timer1
void timer1_pwm_generation(uint8_t duty_cycle1, uint8_t duty_cycle2, uint16_t prescaler, uint16_t frequency, uint8_t use_two_pins, uint8_t mode, uint8_t toggle); // Function to generate PWM signals using Timer1

#endif
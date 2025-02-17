#ifndef UART_HEADER
#define UART_HEADER

#include <avr/io.h>
#include <stdint.h>

typedef enum {
    UART_PARITY_NONE = 0,
    UART_PARITY_EVEN = (1 << UPM00),
    UART_PARITY_ODD = (1 << UPM01) | (1 << UPM00)
} UART_PARITY;

typedef enum {
    UART_STOPBIT_1 = 0,
    UART_STOPBIT_2 = (1 << USBS0)
} UART_STOPBIT;

typedef enum {
    UART_DATABITS_5 = 0,
    UART_DATABITS_6 = (1 << UCSZ00),
    UART_DATABITS_7 = (1 << UCSZ01),
    UART_DATABITS_8 = (1 << UCSZ01) | (1 << UCSZ00)
} UART_DATABITS;

void UART_Init(uint16_t baud_rate, UART_DATABITS data_bits, UART_PARITY parity, UART_STOPBIT stop_bit); // Function to initialize UART with custom settings
uint8_t UART_Available(void); // Function to check if data is available for reading
uint8_t UART_Read(void); // Function to read one byte of data from UART
void UART_Write(uint8_t data); // Function to write one byte of data to UART
void UART_Print(const char *str); // Function to send a string via UART
void timer1_delay_ms(uint16_t delay_ms, uint16_t prescaler); // Function to generate a delay in milliseconds using Timer1

#endif
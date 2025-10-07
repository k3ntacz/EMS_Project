#ifndef UART_H_
#define UART_H_

#include <avr/io.h>                 // Include AVR I/O definitions

#define BAUD 9600                    // UART baud rate
#define MYUBRR ((F_CPU / 16 / BAUD) - 1) // Calculate UBRR register value for UART

void USART0_Init(unsigned int ubrr);

void USART0_Transmit(unsigned char data);

int uart0_putchar(char c, FILE *stream);

/*
int uart0_getchar(FILE *stream) {
	while (!(UCSR0A & (1 << RXC0)));    // Wait for received data
	return UDR0;                         // Return received character
}
*/

FILE uart0_str = FDEV_SETUP_STREAM(uart0_putchar, NULL, _FDEV_SETUP_WRITE); // Setup FILE stream for printf/scanf

#endif

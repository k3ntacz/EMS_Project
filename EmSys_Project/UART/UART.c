#define F_CPU 4915200UL              // Define CPU clock frequency for delay routines
#include <avr/io.h>                 // Include AVR I/O definitions
#include <stdio.h>                  // Include standard I/O (printf)
#include <stdint.h>                 // Include standard integer types (uint8_t, etc.)
#include <avr/pgmspace.h>           // Include program memory access (PROGMEM)
#include <avr/interrupt.h>

#include "UART.h"

void USART0_Init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr >> 8); // Set high byte of UBRR
	UBRR0L = (unsigned char)ubrr;        // Set low byte of UBRR
	UCSR0B = (1 << TXEN0) | (1 << RXEN0); // Enable TX and RX
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00); // Set frame format: 8 data bits, no parity, 1 stop bit (8N1)
}

void USART0_Transmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));   // Wait until data register is empty
	UDR0 = data;                         // Send the data
}

int uart0_putchar(char c, FILE *stream) {
	if (c == '\n') USART0_Transmit('\r'); // Convert newline to carriage return
	USART0_Transmit((unsigned char)c);    // Send character
	return 0;
}

/*
int uart0_getchar(FILE *stream) {
	while (!(UCSR0A & (1 << RXC0)));    // Wait for received data
	return UDR0;                         // Return received character
}
*/

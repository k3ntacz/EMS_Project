#define F_CPU 4915200UL              // Define CPU clock frequency for delay routines
#include <avr/io.h>                 // Include AVR I/O definitions
#include <stdio.h>                  // Include standard I/O (printf)
#include <stdint.h>                 // Include standard integer types (uint8_t, etc.)
#include <avr/pgmspace.h>           // Include program memory access (PROGMEM)
#include <avr/interrupt.h>

#include "SRAM.h"

void SRAM_init(){
	MCUCR |=(1<<SRE);
	SFIOR &= ~(111 << XMM0);
	SFIOR = (1<<XMM2);
}

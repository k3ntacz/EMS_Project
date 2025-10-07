#ifndef UTILS_IO_H_
#define UTILS_IO_H_

#define F_CPU 4915200UL              // Define CPU clock frequency for delay routines
#include <avr/io.h>                 // Include AVR I/O definitions

// LED SNAKE
void light_on(uint8_t LED_N);
void light_off(uint8_t LED_N);
void flashing_light();

#endif

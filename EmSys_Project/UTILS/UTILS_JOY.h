#ifndef UTILS_JOY_H_
#define UTILS_JOY_H_

#include <avr/io.h>                 // Include AVR I/O definitions

#define BUSY_INIT	PD4

// Joystick stuff
uint8_t scale_1_4_to_0_255(uint8_t raw, uint8_t raw_min, uint8_t raw_max);
int16_t scale_voltage(uint8_t raw);		//mV (1 to 4V)

int16_t joystick_angle(uint8_t pos_255);	//not working

const char* joystick_position(uint8_t x255, uint8_t y255);

int8_t button_pressed(uint8_t value_button);	// gives back value of the button (1 if pressed)
char* joystick_pressed(uint8_t b_val);			// says "PRESSED" / "NOT PRESSED"

void show_joystick_values();

#endif

#define F_CPU 4915200UL              // Define CPU clock frequency for delay routines
#include <avr/io.h>                 // Include AVR I/O definitions
#include <stdio.h>                  // Include standard I/O (printf)
#include <stdint.h>                 // Include standard integer types (uint8_t, etc.)
#include <avr/pgmspace.h>           // Include program memory access (PROGMEM)
#include <avr/interrupt.h>

#include "UTILS_JOY.h.h"

uint8_t scale_1_4_to_0_255(uint8_t raw, uint8_t raw_min, uint8_t raw_max) {
	if (raw <= raw_min) return 0;           // Clamp to 0
	if (raw >= raw_max) return 255;         // Clamp to 255
	return (uint8_t)(((uint16_t)(raw - raw_min) * 255) / (raw_max - raw_min)); // Linear scaling
}

int16_t scale_voltage(uint8_t raw) {
	return (int32_t) raw * 3000 /255 + 1000;  //mV (1 to 4V)
}

int16_t joystick_angle(uint8_t pos_255){
	int16_t pos_100=100*pos_255/(255-128) -100;   //not working
	return pos_100;
}

int8_t button_pressed(uint8_t value_button){
	if (value_button < 100) return 1;
	else
		return 0;
}

const char* joystick_position(uint8_t x255,uint8_t y255){
	if (x255 < 50) return "LEFT";           // X low -> LEFT
	if (y255 < 50) return "DOWN";           // Y low -> DOWN
	if (x255 > 200) return "RIGHT";         // X high -> RIGHT
	if (y255 > 200) return "UP";            // Y high -> UP
	return "NEUTRAL";                        // Otherwise NEUTRAL
}

char* joystick_pressed(uint8_t b_val){
	if(b_val) return ("PRESSED");
	else return ("NOT PRESSED");
}

void show_joystick_values(){
	volatile uint8_t* adcMem = (uint8_t*)0x1000;
	adcMem[0] = 1;
	while (!(PIND & (1<<BUSY_INIT))) {}
	
	//PD ADC
	uint8_t x_val = adcMem[0];		// x_axis joystick
	_delay_us(3);
	uint8_t y_val = adcMem[0];		// y_axis joystick
	_delay_us(3);
	uint8_t b_val = adcMem[0];		// button joystick
	
	uint8_t button_val = button_pressed(b_val);

	uint8_t x= scale_1_4_to_0_255(x_val,66,127);
	uint8_t y= scale_1_4_to_0_255(y_val,70,246);
	printf("x_scale:%3u, y_scale:%3u, b_val: %3u\n", x,y,button_val);
	
	/*
		//int16_t Vx = scale_voltage(x);
		//int16_t Vy = scale_voltage(y);
		//printf("x_v:%u, y_v:%u\n", Vx,Vy);
		
		//printf("x_100:%3d y_100:%3d\n",joystick_angle(x),joystick_angle(y));
		*/
	
	printf("position: %s\t button: %s\n",joystick_position(x,y), joystick_pressed(button_val));
}

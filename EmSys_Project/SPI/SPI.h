#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>                 // Include AVR I/O definitions

// --- SPI control pins (hardware SPI) ---
#define SPI_MOSI   	PB5               // MOSI pin number
#define SPI_MISO   	PB6               // MISO pin number
#define SPI_SCK    	PB7               // SCK pin number

// --- Chip-select + OLED control pin ---
#define CAN_CS		PB4				  // Chip select
#define DISP_CS    	PB3               // Chip select pin for OLED
#define IO_CS      	PB2               // Chip select pin for IO (Joystick)
#define DISP_DC	   	PB1               // Data/Command pin for OLED

void spi_init(void);

static inline void spi_write_display_command(uint8_t data);

static inline void spi_write(uint8_t data);

void spi_write_n_bytes(uint8_t slave_pin, uint8_t cmd, const uint8_t *data, uint8_t n); // write n bytes !!! I did not check it !!!!! I am not sure it is working !!!

static inline uint8_t spi_read(void); // read byte

void spi_read_n_bytes_io_and_save_in_array(uint8_t cs, uint8_t n, uint8_t cmd, uint8_t *buffer); // read n bytes

static inline void slave_select(uint8_t slave_pin);

static inline void slave_reset(uint8_t slave_pin);

#endif

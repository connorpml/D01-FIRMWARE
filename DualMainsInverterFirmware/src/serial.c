#include "serial.h"

#define _SERIAL_READ_RETRY_TIMEOUT 100

#define _SERIAL_ENDLINE_CHAR '\n'

struct usart_module _serial_usart_instance;

void serial_init(void) {
	struct usart_config usart_options;
	
	usart_get_config_defaults(&usart_options);
	
	usart_options.baudrate = 9600;
	usart_options.mux_setting = USART_RX_1_TX_2_XCK_3;
	usart_options.pinmux_pad0 = PINMUX_UNUSED;
	usart_options.pinmux_pad1 = PINMUX_PA05D_SERCOM0_PAD1;
	usart_options.pinmux_pad2 = PINMUX_PA04C_SERCOM0_PAD2;
	usart_options.pinmux_pad3 = PINMUX_UNUSED;
	usart_options.transmitter_enable = true;
	usart_options.generator_source = GCLK_GENERATOR_5;
	
	while (usart_init(&_serial_usart_instance, SERCOM0, &usart_options) != STATUS_OK) {
		// pass
	}
	
	usart_enable(&_serial_usart_instance);
}

// Returns null-terminated string
int serial_readline(uint8_t* buffer, int maxlen) {
	bool foundNL = false;
	uint16_t rxdata;
	int buffer_index = 0;
	int retry = 0;
	
	buffer[0] = 0;
	
	while (buffer_index < maxlen && !foundNL) {
		if (usart_read_wait(&_serial_usart_instance, &rxdata) == STATUS_OK) {
			retry = 0;
			
			if (rxdata == _SERIAL_ENDLINE_CHAR) {
				foundNL = true;
				buffer[buffer_index] = 0;
			} else
				buffer[buffer_index++] = rxdata;
		} else {
			retry++;
			
			if (retry >= _SERIAL_READ_RETRY_TIMEOUT)
				break;
				
			delay_us(1000);
		}
	}
	
	if (foundNL)
		return buffer_index;
	else
		return -1;
}

void serial_writeline(uint8_t* buffer, int len) {
	usart_write_buffer_wait(&_serial_usart_instance, buffer, len);
	usart_write_wait(&_serial_usart_instance, _SERIAL_ENDLINE_CHAR);
}

void serial_write_buffer(uint8_t* buffer, int len) {
	usart_write_buffer_wait(&_serial_usart_instance, buffer, len);
}

void serial_write(uint8_t byte) {
	usart_write_wait(&_serial_usart_instance, byte);
}
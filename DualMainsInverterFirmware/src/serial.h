#ifndef SERIAL_H_
#define SERIAL_H_

#include <asf.h>

void serial_init(void);

int serial_readline(uint8_t* buffer, int maxlen);

void serial_writeline(uint8_t* buffer, int len);

void serial_write_buffer(uint8_t* buffer, int len);

void serial_write(uint8_t byte) ;

#endif /* SERIAL_H_ */
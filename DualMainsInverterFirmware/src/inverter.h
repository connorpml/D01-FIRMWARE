#ifndef TC_H_
#define TC_H_

#include <asf.h>

void inverter_init(void);

void inverter_housekeeping(void);

void inverter_set_channels(uint32_t channel_a, uint32_t channel_b);

void _inverter_callback(void);

#endif /* TC_H_ */
#ifndef TCC_H_
#define TCC_H_

#include <asf.h>

typedef enum {
	WFG_CHANNEL_U = 0,
	WFG_CHANNEL_V = 3,
	WFG_CHANNEL_W = 2
} inverter_channel;

void wfg_init(void);

void wfg_channel_set(inverter_channel chan, uint16_t setpoint);

#endif /* TCC_H_ */
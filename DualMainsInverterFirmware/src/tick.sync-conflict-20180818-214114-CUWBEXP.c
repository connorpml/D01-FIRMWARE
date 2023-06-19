/*
 * tick.c
 *
 * Created: 8/22/2016 2:03:23 PM
 *  Author: Connor
 */ 

#include <asf.h>
#include "tick.h"

// _CLOCK_PERIOD -> 48 Megahertz / (4 * 60 hertz * 1024) ~= 195
static const uint16_t _CLOCK_PERIOD = 3137;

static struct tc_module _tc_instance;
static void (*_user_callback)(void); 

static void _callback(struct tc_module *const module_inst)
{
	_user_callback();
}

void tick_init(void (*callback)(void))
{
	_user_callback = callback;
	
	struct tc_config config_tc;
	tc_get_config_defaults(&config_tc);
	config_tc.counter_size = TC_COUNTER_SIZE_16BIT;
	config_tc.wave_generation = TC_WAVE_GENERATION_MATCH_FREQ;
	config_tc.counter_16_bit.compare_capture_channel[0] = _CLOCK_PERIOD;
	config_tc.clock_source = GCLK_GENERATOR_4;
	tc_init(&_tc_instance, TC1, &config_tc);
	tc_enable(&_tc_instance);
	
	tc_register_callback(&_tc_instance, _callback, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&_tc_instance, TC_CALLBACK_CC_CHANNEL0);
}

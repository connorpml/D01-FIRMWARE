/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>

#include <tick.h>
#include <dmi_adc.h>

#define ALPHA 64 // Fixed point. Maximum 1024

#define CONF_MODULE TCC0

// CHANNEL U //
#define CONF_U_CHANNEL 0

#define CONF_HINU_OUTPUT 0
#define CONF_HINU_OUT_PIN PIN_PA14F_TCC0_WO0
#define CONF_HINU_OUT_MUX MUX_PA14F_TCC0_WO0

#define CONF_LINU_OUTPUT 4
#define CONF_LINU_OUT_PIN PIN_PA22F_TCC0_WO4
#define CONF_LINU_OUT_MUX MUX_PA22F_TCC0_WO4

// CHANNEL V //
#define CONF_V_CHANNEL 3

#define CONF_HINV_OUTPUT 3
#define CONF_HINV_OUT_PIN PIN_PA11F_TCC0_WO3
#define CONF_HINV_OUT_MUX MUX_PA11F_TCC0_WO3

#define CONF_LINV_OUTPUT 7
#define CONF_LINV_OUT_PIN PIN_PA17F_TCC0_WO7
#define CONF_LINV_OUT_MUX MUX_PA17F_TCC0_WO7

// CHANNEL W //
#define CONF_W_CHANNEL 2

#define CONF_HINW_OUTPUT 2
#define CONF_HINW_OUT_PIN PIN_PA10F_TCC0_WO2
#define CONF_HINW_OUT_MUX MUX_PA10F_TCC0_WO2

#define CONF_LINW_OUTPUT 6
#define CONF_LINW_OUT_PIN PIN_PA16F_TCC0_WO6
#define CONF_LINW_OUT_MUX MUX_PA16F_TCC0_WO6

/*
static uint16_t sinelut[] = {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,
0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,
0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,
0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,
0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,
0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,
0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,
0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,
};*/


static uint16_t sinelut[] = {
	0x200,0x20d,0x219,0x226,0x232,0x23f,0x24b,0x258,
	0x264,0x271,0x27d,0x289,0x295,0x2a1,0x2ad,0x2b9,
	0x2c5,0x2d0,0x2dc,0x2e7,0x2f2,0x2fd,0x308,0x313,
	0x31d,0x328,0x332,0x33c,0x346,0x350,0x359,0x362,
	0x36b,0x374,0x37c,0x385,0x38d,0x395,0x39c,0x3a4,
	0x3ab,0x3b2,0x3b8,0x3bf,0x3c5,0x3ca,0x3d0,0x3d5,
	0x3da,0x3df,0x3e3,0x3e7,0x3eb,0x3ee,0x3f1,0x3f4,
	0x3f7,0x3f9,0x3fb,0x3fc,0x3fe,0x3ff,0x400,0x400,
	0x400,0x400,0x3ff,0x3fe,0x3fd,0x3fc,0x3fa,0x3f8,
	0x3f5,0x3f3,0x3f0,0x3ec,0x3e9,0x3e5,0x3e1,0x3dc,
	0x3d8,0x3d2,0x3cd,0x3c7,0x3c2,0x3bb,0x3b5,0x3ae,
	0x3a7,0x3a0,0x399,0x391,0x389,0x381,0x378,0x370,
	0x367,0x35e,0x354,0x34b,0x341,0x337,0x32d,0x323,
	0x318,0x30e,0x303,0x2f8,0x2ed,0x2e1,0x2d6,0x2ca,
	0x2bf,0x2b3,0x2a7,0x29b,0x28f,0x283,0x277,0x26a,
	0x25e,0x252,0x245,0x239,0x22c,0x220,0x213,0x206,
	0x1fa,0x1ed,0x1e0,0x1d4,0x1c7,0x1bb,0x1ae,0x1a2,
	0x196,0x189,0x17d,0x171,0x165,0x159,0x14d,0x141,
	0x136,0x12a,0x11f,0x113,0x108,0xfd,0xf2,0xe8,
	0xdd,0xd3,0xc9,0xbf,0xb5,0xac,0xa2,0x99,
	0x90,0x88,0x7f,0x77,0x6f,0x67,0x60,0x59,
	0x52,0x4b,0x45,0x3e,0x39,0x33,0x2e,0x28,
	0x24,0x1f,0x1b,0x17,0x14,0x10,0xd,0xb,
	0x8,0x6,0x4,0x3,0x2,0x1,0x0,0x0,
	0x0,0x0,0x1,0x2,0x4,0x5,0x7,0x9,
	0xc,0xf,0x12,0x15,0x19,0x1d,0x21,0x26,
	0x2b,0x30,0x36,0x3b,0x41,0x48,0x4e,0x55,
	0x5c,0x64,0x6b,0x73,0x7b,0x84,0x8c,0x95,
	0x9e,0xa7,0xb0,0xba,0xc4,0xce,0xd8,0xe3,
	0xed,0xf8,0x103,0x10e,0x119,0x124,0x130,0x13b,
	0x147,0x153,0x15f,0x16b,0x177,0x183,0x18f,0x19c,
	0x1a8,0x1b5,0x1c1,0x1ce,0x1da,0x1e7,0x1f3,0x200
};

struct tcc_module tcc_instance;

static void configure_tcc(void)
{
	struct tcc_config config_tcc;
	tcc_get_config_defaults(&config_tcc, CONF_MODULE);
	config_tcc.counter.clock_source = GCLK_GENERATOR_3;
	config_tcc.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV2;
	config_tcc.counter.period = 1024;
	config_tcc.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	
	config_tcc.compare.match[CONF_U_CHANNEL] = 0;
	
	config_tcc.pins.enable_wave_out_pin[CONF_HINU_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[CONF_HINU_OUTPUT]        = CONF_HINU_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[CONF_HINU_OUTPUT]    = CONF_HINU_OUT_MUX;
	
	config_tcc.pins.enable_wave_out_pin[CONF_LINU_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[CONF_LINU_OUTPUT]        = CONF_LINU_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[CONF_LINU_OUTPUT]    = CONF_LINU_OUT_MUX;
	config_tcc.wave_ext.invert[CONF_U_CHANNEL] = true;
	
	config_tcc.compare.match[CONF_V_CHANNEL] = 0;
	
	config_tcc.pins.enable_wave_out_pin[CONF_HINV_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[CONF_HINV_OUTPUT]        = CONF_HINV_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[CONF_HINV_OUTPUT]    = CONF_HINV_OUT_MUX;
	
	config_tcc.pins.enable_wave_out_pin[CONF_LINV_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[CONF_LINV_OUTPUT]        = CONF_LINV_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[CONF_LINV_OUTPUT]    = CONF_LINV_OUT_MUX;
	config_tcc.wave_ext.invert[CONF_V_CHANNEL] = true;
	
	config_tcc.compare.match[CONF_W_CHANNEL] = 0;
	
	config_tcc.pins.enable_wave_out_pin[CONF_HINW_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[CONF_HINW_OUTPUT]        = CONF_HINW_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[CONF_HINW_OUTPUT]    = CONF_HINW_OUT_MUX;
	
	config_tcc.pins.enable_wave_out_pin[CONF_LINW_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[CONF_LINW_OUTPUT]        = CONF_LINW_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[CONF_LINW_OUTPUT]    = CONF_LINW_OUT_MUX;
	config_tcc.wave_ext.invert[CONF_W_CHANNEL] = true;
	
	tcc_init(&tcc_instance, CONF_MODULE, &config_tcc);

	tcc_enable(&tcc_instance);
}

typedef enum {
	CHANNEL_U = CONF_U_CHANNEL,
	CHANNEL_V = CONF_V_CHANNEL,
	CHANNEL_W = CONF_W_CHANNEL
} inverter_channel;

// setpoint out of 1024
void inverter_set(inverter_channel chan, uint16_t setpoint) {
	tcc_set_compare_value(&tcc_instance,
		(enum tcc_match_capture_channel)chan, (uint32_t)setpoint);
}

volatile enum DmiState {
	DMI_STARTUP,
	DMI_AWAITING_CONVERSION,
	DMI_CONVERSION_READY,
} dmi_state = DMI_STARTUP;

static const int32_t baseline_coefficient = 85000; //42500; // amplitude millivolts
static const int32_t channel_a_target = 85000; // amplitude (peak, not RMS) millivolts
static const int32_t channel_b_target = 85000; // amplitude (peak, not RMS) millivolts

// 1000mV * (470k + 470k) / 2.2k = 427273 mV = full scale voltage on bus when adc reading is 2^12
static const uint32_t adc_fullscale_bus_millivolts = 427273;

volatile bool baseline_enable = false;

void tick_callback(void) {
	static uint16_t i = 0;
	
	uint16_t bus_voltage_raw;
	dmi_adc_read_conversion(&bus_voltage_raw);
	volatile int32_t bus_voltage_unfiltered = (((int32_t)bus_voltage_raw) * adc_fullscale_bus_millivolts) >> 12;
	volatile int32_t bus_voltage = (ALPHA * bus_voltage_unfiltered + (1024 - ALPHA) * bus_voltage) >> 10;
	
	volatile int32_t sineval_raw = (int16_t)sinelut[i] - 512;
	volatile int32_t baseline;
	volatile int32_t chan_a, chan_b;
	
	// Hysteresis loop
	if (baseline_enable && bus_voltage - 5000 < baseline_coefficient) {
		baseline_enable = false;
		port_pin_set_output_level(PIN_PA27, true);
	}
	else if (!baseline_enable && bus_voltage - 12000 > baseline_coefficient) {
		baseline_enable = true;
		port_pin_set_output_level(PIN_PA27, false);
	}
			
	// Check if bus voltage is high enough to generate baseline signal
	if (baseline_enable) {
		baseline =  baseline = baseline_coefficient * sineval_raw / bus_voltage;
		chan_a = baseline - 2 * channel_a_target * sineval_raw / bus_voltage;
		chan_b = baseline - 2 * channel_b_target * sineval_raw / bus_voltage;
	} else {
		// If bus voltage isn't high enough to generate baseline signal, set all outputs to zero.
		baseline = 0;
		chan_a = 0;
		chan_b = 0;
	}
	
	// Up until this point, these values could range from -512 to 512. Shift to unsigned ints
	chan_a = chan_a + 512;
	baseline = baseline + 512;
	chan_b = chan_b + 512;
	
	// Set each channel accordingly
	inverter_set(CHANNEL_U, (uint16_t)chan_a);
	inverter_set(CHANNEL_W, (uint16_t)chan_b);
	inverter_set(CHANNEL_V, (uint16_t)baseline);
	
	i += 1;
	if (i >= (sizeof(sinelut) / sizeof(uint16_t)))
		i = 0;
	
	dmi_adc_start_conversion();
	
	return;
}

int main (void)
{
	system_init();
	delay_init();
	configure_tcc();
	dmi_adc_init();
	tick_init(tick_callback);

	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA23, &config_port_pin);
	port_pin_set_config(PIN_PA27, &config_port_pin);
	port_pin_set_output_level(PIN_PA27, false); // This line might be jacked up

	while (true) {
		port_pin_set_output_level(PIN_PA23, true);
		delay_ms(250);
		port_pin_set_output_level(PIN_PA23, false);
		delay_ms(250);
	}
}

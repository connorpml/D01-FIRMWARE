#include "wfg.h"

#define _WFG_TCC_MODULE TCC0

// CHANNEL U //
#define _WFG_HINU_OUTPUT 0
#define _WFG_HINU_OUT_PIN PIN_PA14F_TCC0_WO0
#define _WFG_HINU_OUT_MUX MUX_PA14F_TCC0_WO0

#define _WFG_LINU_OUTPUT 4
#define _WFG_LINU_OUT_PIN PIN_PA22F_TCC0_WO4
#define _WFG_LINU_OUT_MUX MUX_PA22F_TCC0_WO4

// CHANNEL V //
#define _WFG_HINV_OUTPUT 3
#define _WFG_HINV_OUT_PIN PIN_PA11F_TCC0_WO3
#define _WFG_HINV_OUT_MUX MUX_PA11F_TCC0_WO3

#define _WFG_LINV_OUTPUT 7
#define _WFG_LINV_OUT_PIN PIN_PA17F_TCC0_WO7
#define _WFG_LINV_OUT_MUX MUX_PA17F_TCC0_WO7

// CHANNEL W //
#define _WFG_HINW_OUTPUT 2
#define _WFG_HINW_OUT_PIN PIN_PA10F_TCC0_WO2
#define _WFG_HINW_OUT_MUX MUX_PA10F_TCC0_WO2

#define _WFG_LINW_OUTPUT 6
#define _WFG_LINW_OUT_PIN PIN_PA16F_TCC0_WO6
#define _WFG_LINW_OUT_MUX MUX_PA16F_TCC0_WO6

// DEAD-TIME INSERTION (DTI) //
// minimum 1.5 microsecond dead time
// GCLK_TCC = 48 megahertz
// 1.0 us * 48 megahertz = 48
// This was tested with scope to produce 1uS dead time 11/15/2022
#define DTI_LOW_TIME 24
#define DTI_HIGH_TIME 24

struct tcc_module _wfg_tcc_instance; // Timer/Counter controller for generating waveform signal

void wfg_init(void)
{
	struct tcc_config config_tcc;
	tcc_get_config_defaults(&config_tcc, _WFG_TCC_MODULE);
	config_tcc.counter.clock_source = GCLK_GENERATOR_3;
	config_tcc.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV2;
	config_tcc.counter.period = 1024;
	config_tcc.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	
	config_tcc.compare.match[WFG_CHANNEL_U] = 0;
	
	config_tcc.pins.enable_wave_out_pin[_WFG_HINU_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[_WFG_HINU_OUTPUT]        = _WFG_HINU_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[_WFG_HINU_OUTPUT]    = _WFG_HINU_OUT_MUX;
	
	config_tcc.pins.enable_wave_out_pin[_WFG_LINU_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[_WFG_LINU_OUTPUT]        = _WFG_LINU_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[_WFG_LINU_OUTPUT]    = _WFG_LINU_OUT_MUX;
	//config_tcc.wave_ext.invert[WFG_CHANNEL_U] = true;
	
	config_tcc.compare.match[WFG_CHANNEL_V] = 0;
	
	config_tcc.pins.enable_wave_out_pin[_WFG_HINV_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[_WFG_HINV_OUTPUT]        = _WFG_HINV_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[_WFG_HINV_OUTPUT]    = _WFG_HINV_OUT_MUX;
	
	config_tcc.pins.enable_wave_out_pin[_WFG_LINV_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[_WFG_LINV_OUTPUT]        = _WFG_LINV_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[_WFG_LINV_OUTPUT]    = _WFG_LINV_OUT_MUX;
	//config_tcc.wave_ext.invert[WFG_CHANNEL_V] = true;
	
	config_tcc.compare.match[WFG_CHANNEL_W] = 0;
	
	config_tcc.pins.enable_wave_out_pin[_WFG_HINW_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[_WFG_HINW_OUTPUT]        = _WFG_HINW_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[_WFG_HINW_OUTPUT]    = _WFG_HINW_OUT_MUX;
	
	config_tcc.pins.enable_wave_out_pin[_WFG_LINW_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[_WFG_LINW_OUTPUT]        = _WFG_LINW_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[_WFG_LINW_OUTPUT]    = _WFG_LINW_OUT_MUX;
	//config_tcc.wave_ext.invert[WFG_CHANNEL_W] = true;
	
	tcc_init(&_wfg_tcc_instance, _WFG_TCC_MODULE, &config_tcc);

	_WFG_TCC_MODULE->WEXCTRL.reg |= TCC_WEXCTRL_DTIEN0 | TCC_WEXCTRL_DTIEN1 | TCC_WEXCTRL_DTIEN2 | TCC_WEXCTRL_DTIEN3;
	_WFG_TCC_MODULE->WEXCTRL.reg |= TCC_WEXCTRL_DTLS(DTI_LOW_TIME) | TCC_WEXCTRL_DTHS(DTI_HIGH_TIME);

	tcc_enable(&_wfg_tcc_instance);
}

// setpoint out of 1024
void wfg_channel_set(inverter_channel chan, uint16_t setpoint) {
	tcc_set_compare_value(&_wfg_tcc_instance,
	(enum tcc_match_capture_channel)chan, (uint32_t)setpoint);
}

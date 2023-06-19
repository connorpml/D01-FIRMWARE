#include "dmi_adc.h"

#define ADC_SAMPLE_LENGTH				1
#define PINMUX_ADC						0x1

static struct adc_module _adc_inst;
struct adc_config _adc_config;

void dmi_adc_init(void) {
	struct system_pinmux_config pinmux_config;
	system_pinmux_get_config_defaults(&pinmux_config);
	pinmux_config.input_pull = SYSTEM_PINMUX_PIN_PULL_NONE;
	pinmux_config.mux_position = PINMUX_ADC;
	system_pinmux_pin_set_config(PIN_PA07, &pinmux_config);
	system_pinmux_pin_set_config(PIN_PA02, &pinmux_config);

	adc_get_config_defaults(&_adc_config);
	_adc_config.positive_input = ADC_POSITIVE_INPUT_PIN5;
	_adc_config.negative_input = ADC_NEGATIVE_INPUT_PIN0;
	_adc_config.reference      = ADC_REFERENCE_INT1V;
	_adc_config.clock_source   = GCLK_GENERATOR_5;
	_adc_config.clock_prescaler = ADC_CLOCK_PRESCALER_DIV4;
	_adc_config.sample_length = ADC_SAMPLE_LENGTH;
	_adc_config.gain_factor    = ADC_GAIN_FACTOR_DIV2;
	_adc_config.accumulate_samples = ADC_ACCUMULATE_DISABLE;

	/* Initialize the ADC */
	adc_init(&_adc_inst, ADC, &_adc_config);
	adc_enable(&_adc_inst);
	
	return;
}

bool dmi_adc_read_conversion(uint16_t* result, enum adc_positive_input channel) {
	uint16_t adc_temp;
	
	adc_start_conversion(&_adc_inst);
	while (adc_read(&_adc_inst, &adc_temp) != STATUS_OK) {}

	*result = adc_temp;
	
	return true;
}

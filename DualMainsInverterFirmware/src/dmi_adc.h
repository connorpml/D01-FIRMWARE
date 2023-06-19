#ifndef ADC_H_
#define ADC_H_

#include <asf.h>

void dmi_adc_init(void);

bool dmi_adc_read_conversion(uint16_t*, enum adc_positive_input);

#endif /* ADC_H_ */
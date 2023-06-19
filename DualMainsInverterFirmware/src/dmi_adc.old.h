/*
 * adc.h
 *
 * Created: 7/29/2018 3:56:19 PM
 *  Author: Connor
 */ 


#ifndef ADC_H_
#define ADC_H_

void dmi_adc_init(void);

bool dmi_adc_start_conversion(void);

bool dmi_adc_read_conversion(uint16_t*);

#endif /* ADC_H_ */
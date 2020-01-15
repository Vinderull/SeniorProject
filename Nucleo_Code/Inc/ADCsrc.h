////ADCsrc.h

#ifndef __ADCsrc_H
#define __ADCsrc_H
#include "stm32l4xx_hal.h"

void ADC1_Init(void);

void ADC1_Wakeup(void);

void getFloat(uint32_t *input, float *output, uint32_t nsamp);

void findFrequency(float *samples, uint32_t nsamp, float *note);

void GPIO_Init(void);

void TIM4_Init(void);



void ADC_Calibration(void);


#endif

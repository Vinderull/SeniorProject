////ADCsrc.h

#ifndef __ADCsrc_H
#define __ADCsrc_H

#include "tim.h"

void ADC1_Init(void);

void ADC1_Wakeup(void);

void TIM4_Config(uint16_t fs);

void getFloat(int *input, float *output, int nsamp);

void findFrequency(float *samples, int nsamp, float *note);

void GPIO_Init(void);

void TIM4_Init(void);



void ADC_Calibration(void);


#endif

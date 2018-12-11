////ADCsrc.h

#ifndef __ADCsrc_H
#define __ADCsrc_H


void ADC1_Init(void);

void ADC1_Wakeup(void);

float findFrequency(float *samples, int nsamp);

void GPIO_Init(void);

void TIM4_Init(void);



void ADC_Calibration(void);


#endif

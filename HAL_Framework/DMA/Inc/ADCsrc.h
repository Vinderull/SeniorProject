////ADCsrc.h

#ifndef __ADCsrc_H
#define __ADCsrc_H


void ADC1_Init(void);

void ADC1_Wakeup(void);

void getFloat(int *input, float *output, int nsamp);

void findFrequency(float *samples, int nsamp, float *note);

void GPIO_Init(void);

void TIM4_Init(void);



void ADC_Calibration(void);


#endif

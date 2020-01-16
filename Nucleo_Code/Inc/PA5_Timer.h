//PA5_Timer.h

#ifndef __MAIN_H__
#define __MAIN_H__

void PA5_Timer(void);

void TIM2_Init(void);

int calcBeat(float frequency, float reference);

void TIM2_Strobe(int beat);

#endif

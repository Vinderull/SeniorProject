//PA5_Timer.h

#ifndef __PA5_Timer_H__
#define __PA5_TIMER_H__

void PA5_Timer(void);

void TIM2_Init(void);

int calcBeat(float frequency, float reference);

void TIM2_Strobe(int beat);

#endif

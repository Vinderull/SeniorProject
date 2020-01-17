/*Timer for PA5 and PA5 GPIO inits */
/*Timer 2 channel 1 */

#include "PA5_Timer.h"
#include "stm32l4xx_hal.h"

void PA5_Timer(void)
{
        //Enable the clock to port A
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

        //set pin 5 to I/O Mode as Alternate Function (10)
        GPIOA->MODER &= ~(GPIO_MODER_MODE5_1 | GPIO_MODER_MODE5_0);
        GPIOA->MODER |= GPIO_MODER_MODE5_1;

        //Pin PA5 as AF1
        GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_1;

        //set IO output speed to 40Mhz
        GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5;
        GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5;

        //SET I/O output as push-pull with pull-up/pull-down
        GPIOA->PUPDR |= GPIO_PUPDR_PUPD5;
        //Push-pull (0, Reset)
        GPIOA->OTYPER &= ~(1<<5);

        //Enable clock to Timer 2 CH1
        RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

        //Default Clock: MSI Range 5, 2.097 MHZ
        //set the timer clock frequency as 1000Hz
        //Timer Clock = processor clock
        TIM2->PSC = 2097000/1000 - 1;

        //Auto reload value
        TIM2->ARR = 1000;

        //Compare and output register
        TIM2->CCR1 = 500;

        //set OC1M of channel to 1 to 011:OC1RED toggles when cnt
        TIM2->CCMR1 |= TIM_CCMR1_OC1M_0;

        //enable compare output 1
        TIM2->CCER |= TIM_CCER_CC1E;

        //enable timer 2
        TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_Init(void)
{
        //enable clock
        RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

        //prescalar = 60
        TIM2->PSC = 63;
        TIM2->ARR = 200 - 1;

        //OC1m = 110 for PWM mode 1 output for channel 1
        TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;

        //output 1 preload Enable
        TIM2->CCMR1 |=  TIM_CCMR1_OC1PE;

        //auto reload preload Enable
        TIM2->CR1 |= TIM_CR1_ARPE;

        //Enable output for channel 1
        TIM2->CCER |= TIM_CCER_CC1E;

        //Force update
        TIM2->EGR |= TIM_EGR_UG;

        //clear update flag
        TIM2->SR &= ~TIM_SR_UIF;

        //Enable interrupt on update
        TIM2->DIER |= TIM_DIER_UIE;

        //enable counter
        TIM2->CR1 |= TIM_CR1_CEN;
}

int calcBeat(float frequency, float reference)
{
        float decBeat;

        /*check to see which is bigger. decBeat should be non negative */
        if (frequency > reference)
                decBeat = frequency - reference;

        else
                decBeat = reference - frequency;

        /* If decBeat is 0, don't divide, just return always on */
        /*since it is in perfect tune. This should be rare, but still possible */
        if (decBeat == 0.0)
                return 255;

        decBeat = 1/decBeat;

        /*scale to fix value as int, cast out of float */
        decBeat *= 100;

        return (int) decBeat;

}

void TIM2_Strobe(int beat)
{
        int brightness;
        int stepSize;

        //beating is recipricol of the difference between reference frequency and measured
        TIM4->CCR1 = beat;
}

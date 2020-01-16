/*Timer for PA5 and PA5 GPIO inits */
/*Timer 2 channel 1 */

void PA5_Timer(void)
{
        //Enable the clock to port A
        RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

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

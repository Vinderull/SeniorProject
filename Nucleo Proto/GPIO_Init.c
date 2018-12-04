//GPIO Initialization




void GPIO_Init(void)
{
//Enabled clock for GPIO: A
RCC->AHB2ENR &= ~RCC_AHB2ENR_GPIOAEN;
RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;


/*SET PA1 as analog*/
/*00 = digital input, 01 = digital Output*/
/*10 = alternate function, 11 = analog (default) */
GPIOA->MODER &= ~(3UL<<4);
GPIOA->MODER |= GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1;

/*set firsrt bit of ASCR to close analog switch */
GPIO->ASCR |= GPIO_ASCR_ASC1;



}

///big source file

#include "ADCsrc.h"
#include "stm32l476xx.h"
///ADC1 Initialization
/// NOTE: ADC needs HSI

void ADC1_Init(void)
{
  /*Enable clock to ADC */
  RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;

  /*disable ADC1 by clearing */
  ADC1->CR &= ~ADC_CR_ADEN;

  /*Enable I/O analog switches voltage booster */
  ADC123_COMMON->CCR |= SYSCFG_CFGR1_BOOSTEN;

  /*Enable conversion of internal channels */
  ADC123_COMMON->CCR |= ADC_CCR_VREFEN;

  /*Configure ADC prescalar to select ADC clock frequency */
/*The clock is common for all the ADCs.
0000: input ADC clock not divided
0001: input ADC clock divided by 2
0010: input ADC clock divided by 4
0011: input ADC clock divided by 6
0100: input ADC clock divided by 8
0101: input ADC clock divided by 10
0110: input ADC clock divided by 12
0111: input ADC clock divided by 16
1000: input ADC clock divided by 32
1001: input ADC clock divided by 64
1010: input ADC clock divided by 128
1011: input ADC clock divided by 256
*/
  ADC123_COMMON->CCR &= ~ADC_CCR_PRESC;

  /*configure ADC clock to be synchonous HCLK/1 */
/*
00: CK_ADCx (x=123) (Asynchronous clock mode), generated at product level (refer to
Section 6: Reset and clock control (RCC))
01: HCLK/1 (Synchronous clock mode). This configuration must be enabled only if the AHB
clock prescaler is set to 1 (HPRE[3:0] = 0xxx in RCC_CFGR register) and if the system clock
has a 50% duty cycle.
10: HCLK/2 (Synchronous clock mode)
11: HCLK/4 (Synchronous clock mode)
*/
  ADC123_COMMON->CCR &= ~ADC_CCR_CKMODE;
  ADC123_COMMON->CCR |= ADC_CCR_CKMODE_0;

  /*Configure all ADCs as independent mode */
  ADC123_COMMON->CCR &= ~ADC_CCR_DUAL;

  /*Wait for ADC come out of deep-power-down mode */
  ADC1_Wakeup();

  /*Configure resoltion, 00= 12bit */
  ADC1->CFGR &= ~ADC_CFGR_RES_0;
  ADC1->CFGR &= ~ADC_CFGR_RES_1;

  /*Select right alignment */
  ADC1->CFGR &= ~ADC_CFGR_ALIGN;

  /*Select nnumber of conversions */
  ADC1->SQR1 &= ~(ADC_SQR1_L);

  /*Configure channel 6 as single ended */
  ADC1->DIFSEL &= ~ADC_DIFSEL_DIFSEL_6;

  /*Configure sample time, needs to be long enough for cap of */
  /* sample and hold circuit to be charged */
  /*
  //000: 2.5 ADC clock cycles
  //001: 6.5 ADC clock cycles
  //010: 12.5 ADC clock cycles
  //011: 24.5 ADC clock cycles
  //100: 47.5 ADC clock cycles
  //101: 92.5 ADC clock cycles
  //110: 247.5 ADC clock cycles
  //111: 640.5 ADC clock cycles
 */
  ADC1->SMPR1 &= ~ADC_SMPR1_SMP6;
  ADC1->SMPR1 |= ADC_SMPR1_SMP6_0 | ADC_SMPR1_SMP6_1;

  /*Set ADC in discontinuous mode */
  ADC1->CFGR &= ~ADC_CFGR_CONT;

  /*Select software trigger */
  ADC1->CFGR &= ~ADC_CFGR_EXTEN;

  /*enable ADC1 */
  ADC1->CR &= ~ADC_CR_ADEN;
  ADC->CR |= ADC_CR_ADEN;

  /*wait for ADC1 to be ready */
  while(!(ADC1->ISR & ADC_ISR_ADRDY));
}


/* This ADC1_Wakeup wakes the ADC on the STM32L476 MCU*/

void ADC1_Wakeup(void){
  int wait_time = 0;
  /*Start ADC operations: DEEPPWD = 0: ADC not in deep pwoer mode*/
  /*DEEPPWD = 1: ADC in deep power mode (reset state) */
  if ((ADC1 -> CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD){
    ADC1 -> CR &= ~ADC_CR_DEEPPWD;
  }

  /* Enable the ADC voltage Regulator */
  /* must enable before calibration of ADC, use software
  to wait for regulator startup time */
  ADC1 -> CR |= ADC_CR_ADVREGEN;

  /* wait for ADC regulator */
  wait_time = 20 * (80000000 / 100000);
  while (wait_time != 0){
  wait_time--;
  }

}
//DMA Init


void DMA_Init(int arg)
{
//arg number of conversions
uint16_t ADC_Results[arg];

/* Enable DMA1 Clock */
RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

/*DMA1 channel 1 config for ADC1 */
//disable memory to memory mode
DMA1_Channel1->CCR &= ~DMA_CCR_MEM2MEM;

//Channel Priorty level
// 00 = low, 01 = medium, 10 = high, 11 = very high
//set to high priority
DMA1_Channel1->CCR &= ~DMA_CCR_PL;
DMA1_Channel1->CCR |= DMA_CCR_PL_1;

//peripheral size
//00 = 8bit, 01 = 16-bit, 10 = 32 bit, 11 = reserved
DMA1_Channel1->CCR &= ~DMA_CCR_PSIZE;
DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0;

//Memory size
//00 = 8bit, 01 = 16-bit, 10 = 32 bit, 11 = reserved
DMA1_Channel1->CCR &= ~DMA_CCR_MSIZE;
DMA1_Channel1->CCR |= DMA_CCR_MSIZE_0;

//peripheral increment mode
//0 = disabled, 1 = enabled
DMA1_Channel1->CCR &= ~DMA_CCR_PINC;


//memory increment mode
//0 = disabled, 1 = enabled
DMA1_Channel1->CCR &= ~DMA_CCR_MINC;
DMA1_Channel1->CCR |= DMA_CCR_MINC;

//Circular
// 0 = disabled, 1 = enabled
DMA1_Channel1->CCR |= DMA_CCR_CIRC;

//Data trasnfer rate
//O read from peripheral
//1 read from memory
DMA1_Channel1->CCR &= ~DMA_CCR_DIR;

//number of ADC results to transfer
DMA1_Channel1->CNDTR = arg;

//peripheral address registers
DMA1_Channel1->CPAR = (uint32_t) &(ADC1->DR);

//memory address registers
//ping pong buffer
DMA1_Channel1->CMAR = (uint32_t) pReadyProcess;

//transfer complete interrupt enable
DMA1_Channel1->CCR |= DMA_CCR_TCIE;

//enable DMA INTERRUPT
NVIC_EnableIRQ(DMA1_Channel1_IRQn);


//DMA Channel selection
//map DMA channel 1 to ADC1
//0000: Channel 1 mapped to ADC1
DMA1_CSELR->CSELR &= ~DMA_CSELR_C1S;

//Enable DMA channel
DMA1_Channel1->CCR |= DMA_CCR_EN;

}




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


//TIMER 4 Initialization for ADC

void TIM4_Init(void)
{
  /*Enable Clock for Timer 4 */
  RCC->APB1ENR1 |= RCC_APB1ENR_TIM4EN;

  /*clear edge-aligned mode */
  TIM4->CR1 &= ~TIM_CR1_CMS;

  /*Counting Direction up counting */
  TIM4->CR1 &= ~TIM_CR1_DIR;

  /*Master Mode Selection */
  /*000: UG bit from the EGR register is used as trigger output (TRGO) */
  /*001: Enable - The counter enable signal is used as trigger output (TRGO) */
  /*010: Update - the update event is selected as trigger output (TRGO) */
  /*011: Compare pulse - the trigger output send a positive when CC1IF flag */
  /* CC1IF flag is to be set (Even if it was already high)
  /*100: Compare - OC1REF signal is used as trigger output (TRGO)
  /*101: Compare- OC2REF signal is used as trigger output*/
  /*110: Compare - OC3REF signal "" */
  /*111: Compare - OC4REF signal ""*/

  /*Clear mster mode select */
  TIM4->CR2 &= ~TIM_CR2_MMS

  /*Select 100, OC1REF as trigger */
  TIM4->CR2 |= TIM_CR2_MMS_2;

  /*OC1M: Output compare 1 mode */
  TIM4->CCMR1 &= ~TIM_CCMR1_OC1M;
  /*0110 PWM mode 1*/
  TIM4->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;

  /*Timer driving frequency = 80MHz/(1+PSC) = 80M/(1+7)= 10MHz */
  /*Trigger frequency 10MHz / (1 + ARR)= 10KHz */
  TIM4->PSC = 7;
  TIM4->ARR = 999;
  /*Duty ratio of 50% */
  TIM4->CCR1 = 500;

  /*OC1 Signal is output */
  TIM4->CCER |= TIM_CCER_CC1E;

  /*Enable Timer */
  TIM4->CR1 |= TIM_CR1_CEN;
}

//*ADC DMA IRQ handler*/

void DMA1_IRQHandler(void){

if((DMA1->ISR & DMA_ISR_TCIF1) == DMA_ISR_TCIF1){

  //write 1 to clear flag
  DMA->IFCR |= DMA_IFCR_CTCIF1;

  if (pReadyWrite = Buffer_Pong){
    pReadyWrite = Buffer_Pong;
    pReadyProcess = Buffer_Ping;
  }
  else{
    pReadyWrite = Buffer_Ping;
    pReadyProcess = BUffer_Pong;
  }

  //DMA memory address
  DMA1_Channel1->CMAR = (uint32_t) pReadyWrite;
  ADC_DMA_DONE = 1;
 }

//clear flags
DMA1->IFCR |= (DMA_IFCR_CHTIF1 | DMA_IFCR_CGIF1 | DMA_IFCR_CTEIF1);
}

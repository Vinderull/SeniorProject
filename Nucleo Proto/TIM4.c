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

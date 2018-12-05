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
  while(!(ADC1->ISR | ADC_ISR_ADRDY));
}

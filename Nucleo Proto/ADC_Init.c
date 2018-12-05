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
  ADC123_COMMON->CCR &= ~ADC_CCR_PRESC;

  /*configure ADC clock to be synchonous HCLK/1 */
  ADC123_COMMON->CCR &= ~ADC_CCR_CKMODE;

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
 //000: 2.5 ADC clock cycles
///001: 6.5 ADC clock cycles
//010: 12.5 ADC clock cycles
//011: 24.5 ADC clock cycles
//100: 47.5 ADC clock cycles
//101: 92.5 ADC clock cycles
//110: 247.5 ADC clock cycles
///111: 640.5 ADC clock cycles
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
  while(!(ADC1->ISR | ADC_ISR_ADRDY))
}

/* The function described below calibrates the ADC after wake up*/

void ADC_Calibration(void){
  /*Make sure the ADC is off*/
  ADC1 -> CR &= ~ADC_CR_ADEN

  /*Wait until ADRDY is reset by the hardware*/
  while((ADC1 -> ISR & ADC_ISR_ADRDY) == ADC_ISR_ADRDY);

  /*Calibrate for single ended ADC input*/
  /*ADCALDIF = 0: Single ended, = 1 for differential input*/
  ADC1 -> CR &= ~ADC_CR_CALDIF;

  /*ADC Calibration can only happen when ADEN = 0 which is disabled*/
  /*Each ADC provides automatic calibration procedure*/
  ADC1 -> CR |= ADC_CR_ADCAL;

  /*ADCAL stays at 1 during the entire calibration process*/
  /*cleared by hardware after calibration is complete, needs to wait*/
  while((ADC1 -> CR & ADC_CR_ADCAL) == ADC_CR_ADCAL);

}

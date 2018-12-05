/* This ADC1_Wakeup wakes the ADC on the STM32L476 MCU*/

void ADC1_Wakeup (void) {
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

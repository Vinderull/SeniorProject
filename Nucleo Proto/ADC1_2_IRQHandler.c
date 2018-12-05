/* This function is for interrupt handling for the ADC on the STM32L476*/

  void ADC1_2_IRQHandler (void){
    if ((ADC1 -> ISR & ADC_ISR_EOC) == ADC_ISR_EOC){
      /* For regular channel, check end of conversion flag (EOC)*/
      /*Reading DR, the ADC register clears the EOC flag*/
      Result = ADC1 -> DR;
    } else if ((ADC1 -> ISR & ADC_ISR_JEOS) == ADC_ISR_JEOS){
      /*For injected channels, check end of sequence flags (JEOS)*/
      /*Reading injected data registers does not clear JEOS flag*/
      /*Each injected channel has a dedicated data register*/
      /*Each hata register is JDRx where x is the number of the channel*/
      Result_1 = ADC1 -> ADC1 -> JDR1;
      /*Clear the flag by writing 1 to it*/
      ADC1 -> ISR |= ADC_ISR_EOS;
    }
  }

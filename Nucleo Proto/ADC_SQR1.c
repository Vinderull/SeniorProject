/*This function configures the ADC covnersion sequence*/

void ADC1_SQR1_CONFIG (void){
  /* ADC regular sequence register 1 (ADC_SQR1)*/
  /* 00000: 1 conversion is in the regular channel conversion sequence*/
  ADC1 -> SQR1 &= ~ADC_SQR1_L;

  /* Specify the channel number of the 1st conversion in regular sequence*/
  ADC1 -> SQR1 &= ~ADC_SQR1_SQ1;
  ADC1 -> SQR1 |= ( 6U << 6);             //PA1 ADC12_IN6
  ADC1 -> DIFSEL &= ~ADC_DIFSEL_DIFSEL_6; //Single-Ended for PA1: ADC12_IN6
}

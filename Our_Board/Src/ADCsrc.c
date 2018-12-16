///big source file

#include "ADCsrc.h"
#include "stm32l476xx.h"
#include "arm_math.h"




///ADC1 Initialization
/// NOTE: ADC needs HSI


void TIM4_Config(uint16_t fs)
 {
static TIM_HandleTypeDef htim;
TIM_MasterConfigTypeDef  sMasterConfig;

htim.Instance = TIM4;

  /* Number of timer counts per ADC sample....  The timer 4 clock frequency is
  * the APB1 Bus frequency: 80 MHz.  For example, To get 50 ksps, we're
  * counting (50 MHz)/(50 ksps) = 1600 counts
  */
  htim.Init.Period = fs;
  htim.Init.Prescaler = 0;
  htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim.Init.CounterMode = TIM_COUNTERMODE_UP;
  HAL_TIM_Base_Init(&htim);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

  HAL_TIMEx_MasterConfigSynchronization(&htim, &sMasterConfig);

  /*##-2- Enable TIM peripheral counter ######################################*/
  HAL_TIM_Base_Start(&htim);
}

void ADC1_Init(void)
{
  /*Enable clock to ADC */
  RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;

  /*disable ADC1 by clearing */
  ADC1->CR &= ~ADC_CR_ADEN;


  /*Enable I/O analog switches voltage booster */
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_BOOSTEN;

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
  ADC123_COMMON->CCR |= ADC_CCR_PRESC_0;

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
  ADC1->CFGR |= ADC_CFGR_ALIGN;

  /*Select nnumber of conversions */
  ADC1->SQR1 &= ~(ADC_SQR1_L);

  //select channel 6 for conversions
  ADC1->SQR1 |= ADC_SQR1_SQ1_2 | ADC_SQR1_SQ1_1;

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
  ADC1->SMPR1 |= ADC_SMPR1_SMP6_0 | ADC_SMPR1_SMP6_2;

  /*Set ADC in discontinuous mode */
  // 0 = discontinuous
  // 1 = continuous
  ADC1->CFGR &= ~ADC_CFGR_CONT;
  //ADC1->CFGR |= ADC_CFGR_CONT;

  // configure ADC for DMA in circular mode
  ADC1->CFGR |= ADC_CFGR_DMACFG;
  //DMA enable?
  ADC1->CFGR |= ADC_CFGR_DMAEN;

  /* set overrun to overwrite */
  ADC1->CFGR |= ADC_CFGR_OVRMOD;
  //ADC1->CFGR &= ~ADC_CFGR_OVRMOD;




    //select TIm4_TRGO
    ADC1->CFGR &= ~ADC_CFGR_EXTSEL;
    ADC1->CFGR |= ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2;

  /*Select software trigger */
  //select rising edge of hardware triggers
  // 00: software triggers
  // 01: hardware trigger, rising edge
  // 10 HW trig, falling edge
  // 11:HW trigg, both
  ADC1->CFGR &= ~ADC_CFGR_EXTEN;
  ADC1->CFGR |= ADC_CFGR_EXTEN_0;

  /*enable end of conversion flag */
   ADC1->IER |= ADC_IER_EOCIE;

  //set DMA interrupt priority
  NVIC_SetPriority(ADC1_2_IRQn, 0);

  //enable DMA INTERRUPT
  NVIC_EnableIRQ(ADC1_2_IRQn);
  //trigger becomes immediately effective once software starts ADC
  ADC1->CR |= ADC_CR_ADSTART;

  /*enable ADC1 */
  ADC1->CR &= ~ADC_CR_ADEN;
  ADC1->CR |= ADC_CR_ADEN;

  /*wait for ADC1 to be ready */
  while(!(ADC1->ISR & ADC_ISR_ADRDY));
}


/* This ADC1_Wakeup wakes the ADC on the STM32L476 MCU*/

void ADC1_Wakeup(void){
  int wait_time = 0;
  /*Start ADC operations: DEEPPWD = 0: ADC not in deep pwoer mode*/
  /*DEEPPWD = 1: ADC in deep power mode (reset state) */
  if ((ADC1->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD){
    ADC1->CR &= ~ADC_CR_DEEPPWD;
  }

  /* Enable the ADC voltage Regulator */
  /* must enable before calibration of ADC, use software */
  /* to wait for regulator startup time */
  ADC1->CR |= ADC_CR_ADVREGEN;

  /* wait for ADC regulator */
  wait_time = 20 * (80000000 / 100000);
  while (wait_time != 0){
  wait_time--;
  }

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
GPIOA->MODER &= ~GPIO_MODER_MODE1;
GPIOA->MODER |= GPIO_MODER_MODE1_0 | GPIO_MODER_MODE1_1;


//clear pupdr
GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD1;

/*set firsrt bit of ASCR to close analog switch */
GPIOA->ASCR |= GPIO_ASCR_ASC1;



}


//TIMER 4 Initialization for ADC

void TIM4_Init(void)
{
  /*Enable Clock for Timer 4 */
  RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;

  /*clear edge-aligned mode */
  TIM4->CR1 &= ~TIM_CR1_CMS;

  /*Counting Direction up counting */
  TIM4->CR1 &= ~TIM_CR1_DIR;

  /*Master Mode Selection */
  /*000: UG bit from the EGR register is used as trigger output (TRGO) */
  /*001: Enable - The counter enable signal is used as trigger output (TRGO) */
  /*010: Update - the update event is selected as trigger output (TRGO) */
  /*011: Compare pulse - the trigger output send a positive when CC1IF flag */
  /* CC1IF flag is to be set (Even if it was already high) */
  /*100: Compare - OC1REF signal is used as trigger output (TRGO)
  /*101: Compare- OC2REF signal is used as trigger output*/
  /*110: Compare - OC3REF signal "" */
  /*111: Compare - OC4REF signal ""*/

  /*Clear mster mode select */
  TIM4->CR2 &= ~TIM_CR2_MMS;

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




/* The function described below calibrates the ADC after wake up*/

void ADC_Calibration(void){
  /*Make sure the ADC is off*/
  ADC1 -> CR &= ~ADC_CR_ADEN;

  /*Wait until ADRDY is reset by the hardware*/
  while((ADC1 -> ISR & ADC_ISR_ADRDY) == ADC_ISR_ADRDY);

  /*Calibrate for single ended ADC input*/
  /*ADCALDIF = 0: Single ended, = 1 for differential input*/
  ADC1 -> CR &= ~ADC_CR_ADCALDIF;

  /*ADC Calibration can only happen when ADEN = 0 which is disabled*/
  /*Each ADC provides automatic calibration procedure*/
  ADC1 -> CR |= ADC_CR_ADCAL;

  /*ADCAL stays at 1 during the entire calibration process*/
  /*cleared by hardware after calibration is complete, needs to wait*/
  while((ADC1 -> CR & ADC_CR_ADCAL) == ADC_CR_ADCAL);

}

void getFloat(uint32_t *input, float *output, int nsamp)
{
  int i;

  // Now convert the valid ADC data into the caller's array of floats.
  // Samples are normalized to range from -1.0 to 1.0
  // 1/32768 = 3.0517578e-05  (Multiplication is much faster than dividing)

  for (i=0; i<nsamp; i++) {
     // 1/32768 = 3.0517578e-05  (Multiplication is much faster than dividing)
        output[i] = ((float)((int)input[i]-32767))*3.0517578e-05f;
      }

}


void findFrequency(float *samples, int nsamp, float *note)
{
   uint32_t i, n, j, maxIndex;
   float avg, dev, maxVal;
   float output1[nsamp*2], output2[nsamp], input[nsamp];
   n=1;


 arm_correlate_f32(samples, nsamp, samples, nsamp, output1);


  arm_mean_f32(output1, nsamp*2, &avg);




/* subtract mean */
for(i=0; i<nsamp*2; i++){
  output1[i] -= avg;

}

  /*Find Max value as well as corresponding index of said value */
   arm_max_f32(output1, nsamp*2, &maxVal, &maxIndex);


/* normalize */
   for(i=0; i<nsamp*2; i++){
     output1[i] /= maxVal;
   }



   /* set origin of autocorre to be max peak */
   for(i=0; i<nsamp; i++){
     output2[i] = output1[maxIndex+i];
}

/*find std deviation and mean of normalized signal */
 arm_mean_f32(output2, nsamp, &avg);
 arm_std_f32(output2, nsamp, &dev);



/* eliminate non dominant peaks */
 for(i=0; i<nsamp; i++){
  if ((output2[i] < avg + (2*dev))) output2[i] = 0.0;
 }


/* peak detection */
   for(i = 1; i<nsamp-1; i++ ){

      if(((output2[i] - output2[i-1])>0) && ((output2[i+1]-output2[i])<0)){
        n = i;
        break;
      }

      else if((output2[i] - output2[i-1])>0) continue;

      else if((output2[i+1] - output2[i]) < 0) continue;
   }

          /*sample rate /divided by number of samples to peak */
          /*returns frequency in Hz */
   *note = 10000.0/((float) n);



  //printf("%f\n\r", note);


}








/* ----------------------------------------------------------------------
* Copyright (C) 2010-2014 ARM Limited. All rights reserved.
*
* $Date:        19. March 2015
* $Revision: 	V.1.4.5
*
* Project: 	    CMSIS DSP Library
* Title:		arm_mean_f32.c
*
* Description:	Mean value of a floating-point vector.
*
* Target Processor: Cortex-M4/Cortex-M3/Cortex-M0
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*   - Neither the name of ARM LIMITED nor the names of its contributors
*     may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
* ---------------------------------------------------------------------------- */



/**
 * @ingroup groupStats
 */

/**
 * @defgroup mean Mean
 *
 * Calculates the mean of the input vector. Mean is defined as the average of the elements in the vector.
 * The underlying algorithm is used:
 *
 * <pre>
 * 	Result = (pSrc[0] + pSrc[1] + pSrc[2] + ... + pSrc[blockSize-1]) / blockSize;
 * </pre>
 *
 * There are separate functions for floating-point, Q31, Q15, and Q7 data types.
 */

/**
 * @addtogroup mean
 * @{
 */


/**
 * @brief Mean value of a floating-point vector.
 * @param[in]       *pSrc points to the input vector
 * @param[in]       blockSize length of the input vector
 * @param[out]      *pResult mean value returned here
 * @return none.
 */


void arm_mean_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult)
{
  float32_t sum = 0.0f;                          /* Temporary result storage */
  uint32_t blkCnt;                               /* loop counter */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  float32_t in1, in2, in3, in4;

  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */
    in1 = *pSrc++;
    in2 = *pSrc++;
    in3 = *pSrc++;
    in4 = *pSrc++;

    sum += in1;
    sum += in2;
    sum += in3;
    sum += in4;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4u;

#else

  /* Run the below code for Cortex-M0 */

  /* Loop over blockSize number of values */
  blkCnt = blockSize;

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

  while(blkCnt > 0u)
  {
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */
    sum += *pSrc++;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) / blockSize  */
  /* Store the result to the destination */
  *pResult = sum / (float32_t) blockSize;
}

/**
 * @} end of mean group
 */



 /* ----------------------------------------------------------------------
 * Copyright (C) 2010-2014 ARM Limited. All rights reserved.
 *
 * $Date:        19. March 2015
 * $Revision: 	V.1.4.5
 *
 * Project: 	    CMSIS DSP Library
 * Title:		arm_std_f32.c
 *
 * Description:	Standard deviation of the elements of a floating-point vector.
 *
 * Target Processor: Cortex-M4/Cortex-M3/Cortex-M0
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   - Neither the name of ARM LIMITED nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * ---------------------------------------------------------------------------- */



 /**
  * @ingroup groupStats
  */

 /**
  * @defgroup STD Standard deviation
  *
  * Calculates the standard deviation of the elements in the input vector.
  * The underlying algorithm is used:
  *
  * <pre>
  * 	Result = sqrt((sumOfSquares - sum<sup>2</sup> / blockSize) / (blockSize - 1))
  *
  *	   where, sumOfSquares = pSrc[0] * pSrc[0] + pSrc[1] * pSrc[1] + ... + pSrc[blockSize-1] * pSrc[blockSize-1]
  *
  *	                   sum = pSrc[0] + pSrc[1] + pSrc[2] + ... + pSrc[blockSize-1]
  * </pre>
  *
  * There are separate functions for floating point, Q31, and Q15 data types.
  */

 /**
  * @addtogroup STD
  * @{
  */


 /**
  * @brief Standard deviation of the elements of a floating-point vector.
  * @param[in]       *pSrc points to the input vector
  * @param[in]       blockSize length of the input vector
  * @param[out]      *pResult standard deviation value returned here
  * @return none.
  *
  */


 void arm_std_f32(
   float32_t * pSrc,
   uint32_t blockSize,
   float32_t * pResult)
 {
   float32_t sum = 0.0f;                          /* Temporary result storage */
   float32_t sumOfSquares = 0.0f;                 /* Sum of squares */
   float32_t in;                                  /* input value */
   uint32_t blkCnt;                               /* loop counter */

 #ifndef ARM_MATH_CM0_FAMILY

   /* Run the below code for Cortex-M4 and Cortex-M3 */

   float32_t meanOfSquares, mean, squareOfMean;

 	if(blockSize == 1)
 	{
 		*pResult = 0;
 		return;
 	}

   /*loop Unrolling */
   blkCnt = blockSize >> 2u;

   /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
    ** a second loop below computes the remaining 1 to 3 samples. */
   while(blkCnt > 0u)
   {
     /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1])  */
     /* Compute Sum of squares of the input samples
      * and then store the result in a temporary variable, sum. */
     in = *pSrc++;
     sum += in;
     sumOfSquares += in * in;
     in = *pSrc++;
     sum += in;
     sumOfSquares += in * in;
     in = *pSrc++;
     sum += in;
     sumOfSquares += in * in;
     in = *pSrc++;
     sum += in;
     sumOfSquares += in * in;

     /* Decrement the loop counter */
     blkCnt--;
   }

   /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
    ** No loop unrolling is used. */
   blkCnt = blockSize % 0x4u;

   while(blkCnt > 0u)
   {
     /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */
     /* Compute Sum of squares of the input samples
      * and then store the result in a temporary variable, sum. */
     in = *pSrc++;
     sum += in;
     sumOfSquares += in * in;

     /* Decrement the loop counter */
     blkCnt--;
   }

   /* Compute Mean of squares of the input samples
    * and then store the result in a temporary variable, meanOfSquares. */
   meanOfSquares = sumOfSquares / ((float32_t) blockSize - 1.0f);

   /* Compute mean of all input values */
   mean = sum / (float32_t) blockSize;

   /* Compute square of mean */
   squareOfMean = (mean * mean) * (((float32_t) blockSize) /
                                   ((float32_t) blockSize - 1.0f));

   /* Compute standard deviation and then store the result to the destination */
   arm_sqrt_f32((meanOfSquares - squareOfMean), pResult);

 #else

   /* Run the below code for Cortex-M0 */

   float32_t squareOfSum;                         /* Square of Sum */
   float32_t var;                                 /* Temporary varaince storage */

 	if(blockSize == 1)
 	{
 		*pResult = 0;
 		return;
 	}

   /* Loop over blockSize number of values */
   blkCnt = blockSize;

   while(blkCnt > 0u)
   {
     /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */
     /* Compute Sum of squares of the input samples
      * and then store the result in a temporary variable, sumOfSquares. */
     in = *pSrc++;
     sumOfSquares += in * in;

     /* C = (A[0] + A[1] + ... + A[blockSize-1]) */
     /* Compute Sum of the input samples
      * and then store the result in a temporary variable, sum. */
     sum += in;

     /* Decrement the loop counter */
     blkCnt--;
   }

   /* Compute the square of sum */
   squareOfSum = ((sum * sum) / (float32_t) blockSize);

   /* Compute the variance */
   var = ((sumOfSquares - squareOfSum) / (float32_t) (blockSize - 1.0f));

   /* Compute standard deviation and then store the result to the destination */
   arm_sqrt_f32(var, pResult);

 #endif /* #ifndef ARM_MATH_CM0_FAMILY */

 }

 /**
  * @} end of STD group
  */


  /* ----------------------------------------------------------------------
  * Copyright (C) 2010-2014 ARM Limited. All rights reserved.
  *
  * $Date:        19. March 2015
  * $Revision: 	V.1.4.5
  *
  * Project: 	    CMSIS DSP Library
  * Title:		arm_max_f32.c
  *
  * Description:	Maximum value of a floating-point vector.
  *
  * Target Processor: Cortex-M4/Cortex-M3/Cortex-M0
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions
  * are met:
  *   - Redistributions of source code must retain the above copyright
  *     notice, this list of conditions and the following disclaimer.
  *   - Redistributions in binary form must reproduce the above copyright
  *     notice, this list of conditions and the following disclaimer in
  *     the documentation and/or other materials provided with the
  *     distribution.
  *   - Neither the name of ARM LIMITED nor the names of its contributors
  *     may be used to endorse or promote products derived from this
  *     software without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  * POSSIBILITY OF SUCH DAMAGE.
  * ---------------------------------------------------------------------------- */



  /**
   * @ingroup groupStats
   */

  /**
   * @defgroup Max Maximum
   *
   * Computes the maximum value of an array of data.
   * The function returns both the maximum value and its position within the array.
   * There are separate functions for floating-point, Q31, Q15, and Q7 data types.
   */

  /**
   * @addtogroup Max
   * @{
   */


  /**
   * @brief Maximum value of a floating-point vector.
   * @param[in]       *pSrc points to the input vector
   * @param[in]       blockSize length of the input vector
   * @param[out]      *pResult maximum value returned here
   * @param[out]      *pIndex index of maximum value returned here
   * @return none.
   */

  void arm_max_f32(
    float32_t * pSrc,
    uint32_t blockSize,
    float32_t * pResult,
    uint32_t * pIndex)
  {
  #ifndef ARM_MATH_CM0_FAMILY

    /* Run the below code for Cortex-M4 and Cortex-M3 */
    float32_t maxVal1, maxVal2, out;               /* Temporary variables to store the output value. */
    uint32_t blkCnt, outIndex, count;              /* loop counter */

    /* Initialise the count value. */
    count = 0u;
    /* Initialise the index value to zero. */
    outIndex = 0u;
    /* Load first input value that act as reference value for comparision */
    out = *pSrc++;

    /* Loop unrolling */
    blkCnt = (blockSize - 1u) >> 2u;

    /* Run the below code for Cortex-M4 and Cortex-M3 */
    while(blkCnt > 0u)
    {
      /* Initialize maxVal to the next consecutive values one by one */
      maxVal1 = *pSrc++;

      maxVal2 = *pSrc++;

      /* compare for the maximum value */
      if(out < maxVal1)
      {
        /* Update the maximum value and its index */
        out = maxVal1;
        outIndex = count + 1u;
      }

      maxVal1 = *pSrc++;

      /* compare for the maximum value */
      if(out < maxVal2)
      {
        /* Update the maximum value and its index */
        out = maxVal2;
        outIndex = count + 2u;
      }

      maxVal2 = *pSrc++;

      /* compare for the maximum value */
      if(out < maxVal1)
      {
        /* Update the maximum value and its index */
        out = maxVal1;
        outIndex = count + 3u;
      }

      /* compare for the maximum value */
      if(out < maxVal2)
      {
        /* Update the maximum value and its index */
        out = maxVal2;
        outIndex = count + 4u;
      }

      count += 4u;

      /* Decrement the loop counter */
      blkCnt--;
    }

    /* if (blockSize - 1u) is not multiple of 4 */
    blkCnt = (blockSize - 1u) % 4u;

  #else

    /* Run the below code for Cortex-M0 */
    float32_t maxVal1, out;                        /* Temporary variables to store the output value. */
    uint32_t blkCnt, outIndex;                     /* loop counter */

    /* Initialise the index value to zero. */
    outIndex = 0u;
    /* Load first input value that act as reference value for comparision */
    out = *pSrc++;

    blkCnt = (blockSize - 1u);

  #endif /* #ifndef ARM_MATH_CM0_FAMILY */

    while(blkCnt > 0u)
    {
      /* Initialize maxVal to the next consecutive values one by one */
      maxVal1 = *pSrc++;

      /* compare for the maximum value */
      if(out < maxVal1)
      {
        /* Update the maximum value and it's index */
        out = maxVal1;
        outIndex = blockSize - blkCnt;
      }


      /* Decrement the loop counter */
      blkCnt--;

    }

    /* Store the maximum value and it's index into destination pointers */
    *pResult = out;
    *pIndex = outIndex;
  }

  /**
   * @} end of Max group
   */




   /* ----------------------------------------------------------------------------
   * Copyright (C) 2010-2014 ARM Limited. All rights reserved.
   *
   * $Date:        19. March 2015
   * $Revision: 	V.1.4.5
   *
   * Project: 	    CMSIS DSP Library
   * Title:		arm_correlate_f32.c
   *
   * Description:	 Correlation of floating-point sequences.
   *
   * Target Processor: Cortex-M4/Cortex-M3/Cortex-M0
   *
   * Redistribution and use in source and binary forms, with or without
   * modification, are permitted provided that the following conditions
   * are met:
   *   - Redistributions of source code must retain the above copyright
   *     notice, this list of conditions and the following disclaimer.
   *   - Redistributions in binary form must reproduce the above copyright
   *     notice, this list of conditions and the following disclaimer in
   *     the documentation and/or other materials provided with the
   *     distribution.
   *   - Neither the name of ARM LIMITED nor the names of its contributors
   *     may be used to endorse or promote products derived from this
   *     software without specific prior written permission.
   *
   * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
   * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
   * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
   * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
   * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
   * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   * POSSIBILITY OF SUCH DAMAGE.
   * -------------------------------------------------------------------------- */



   /**
    * @ingroup groupFilters
    */

   /**
    * @defgroup Corr Correlation
    *
    * Correlation is a mathematical operation that is similar to convolution.
    * As with convolution, correlation uses two signals to produce a third signal.
    * The underlying algorithms in correlation and convolution are identical except that one of the inputs is flipped in convolution.
    * Correlation is commonly used to measure the similarity between two signals.
    * It has applications in pattern recognition, cryptanalysis, and searching.
    * The CMSIS library provides correlation functions for Q7, Q15, Q31 and floating-point data types.
    * Fast versions of the Q15 and Q31 functions are also provided.
    *
    * \par Algorithm
    * Let <code>a[n]</code> and <code>b[n]</code> be sequences of length <code>srcALen</code> and <code>srcBLen</code> samples respectively.
    * The convolution of the two signals is denoted by
    * <pre>
    *                   c[n] = a[n] * b[n]
    * </pre>
    * In correlation, one of the signals is flipped in time
    * <pre>
    *                   c[n] = a[n] * b[-n]
    * </pre>
    *
    * \par
    * and this is mathematically defined as
    * \image html CorrelateEquation.gif
    * \par
    * The <code>pSrcA</code> points to the first input vector of length <code>srcALen</code> and <code>pSrcB</code> points to the second input vector of length <code>srcBLen</code>.
    * The result <code>c[n]</code> is of length <code>2 * max(srcALen, srcBLen) - 1</code> and is defined over the interval <code>n=0, 1, 2, ..., (2 * max(srcALen, srcBLen) - 2)</code>.
    * The output result is written to <code>pDst</code> and the calling function must allocate <code>2 * max(srcALen, srcBLen) - 1</code> words for the result.
    *
    * <b>Note</b>
    * \par
    * The <code>pDst</code> should be initialized to all zeros before being used.
    *
    * <b>Fixed-Point Behavior</b>
    * \par
    * Correlation requires summing up a large number of intermediate products.
    * As such, the Q7, Q15, and Q31 functions run a risk of overflow and saturation.
    * Refer to the function specific documentation below for further details of the particular algorithm used.
    *
    *
    * <b>Fast Versions</b>
    *
    * \par
    * Fast versions are supported for Q31 and Q15.  Cycles for Fast versions are less compared to Q31 and Q15 of correlate and the design requires
    * the input signals should be scaled down to avoid intermediate overflows.
    *
    *
    * <b>Opt Versions</b>
    *
    * \par
    * Opt versions are supported for Q15 and Q7.  Design uses internal scratch buffer for getting good optimisation.
    * These versions are optimised in cycles and consumes more memory(Scratch memory) compared to Q15 and Q7 versions of correlate
    */

   /**
    * @addtogroup Corr
    * @{
    */
   /**
    * @brief Correlation of floating-point sequences.
    * @param[in]  *pSrcA points to the first input sequence.
    * @param[in]  srcALen length of the first input sequence.
    * @param[in]  *pSrcB points to the second input sequence.
    * @param[in]  srcBLen length of the second input sequence.
    * @param[out] *pDst points to the location where the output result is written.  Length 2 * max(srcALen, srcBLen) - 1.
    * @return none.
    */

   void arm_correlate_f32(
     float32_t * pSrcA,
     uint32_t srcALen,
     float32_t * pSrcB,
     uint32_t srcBLen,
     float32_t * pDst)
   {


   #ifndef ARM_MATH_CM0_FAMILY

     /* Run the below code for Cortex-M4 and Cortex-M3 */

     float32_t *pIn1;                               /* inputA pointer */
     float32_t *pIn2;                               /* inputB pointer */
     float32_t *pOut = pDst;                        /* output pointer */
     float32_t *px;                                 /* Intermediate inputA pointer */
     float32_t *py;                                 /* Intermediate inputB pointer */
     float32_t *pSrc1;                              /* Intermediate pointers */
     float32_t sum, acc0, acc1, acc2, acc3;         /* Accumulators */
     float32_t x0, x1, x2, x3, c0;                  /* temporary variables for holding input and coefficient values */
     uint32_t j, k = 0u, count, blkCnt, outBlockSize, blockSize1, blockSize2, blockSize3;  /* loop counters */
     int32_t inc = 1;                               /* Destination address modifier */


     /* The algorithm implementation is based on the lengths of the inputs. */
     /* srcB is always made to slide across srcA. */
     /* So srcBLen is always considered as shorter or equal to srcALen */
     /* But CORR(x, y) is reverse of CORR(y, x) */
     /* So, when srcBLen > srcALen, output pointer is made to point to the end of the output buffer */
     /* and the destination pointer modifier, inc is set to -1 */
     /* If srcALen > srcBLen, zero pad has to be done to srcB to make the two inputs of same length */
     /* But to improve the performance,
      * we assume zeroes in the output instead of zero padding either of the the inputs*/
     /* If srcALen > srcBLen,
      * (srcALen - srcBLen) zeroes has to included in the starting of the output buffer */
     /* If srcALen < srcBLen,
      * (srcALen - srcBLen) zeroes has to included in the ending of the output buffer */
     if(srcALen >= srcBLen)
     {
       /* Initialization of inputA pointer */
       pIn1 = pSrcA;

       /* Initialization of inputB pointer */
       pIn2 = pSrcB;

       /* Number of output samples is calculated */
       outBlockSize = (2u * srcALen) - 1u;

       /* When srcALen > srcBLen, zero padding has to be done to srcB
        * to make their lengths equal.
        * Instead, (outBlockSize - (srcALen + srcBLen - 1))
        * number of output samples are made zero */
       j = outBlockSize - (srcALen + (srcBLen - 1u));

       /* Updating the pointer position to non zero value */
       pOut += j;

       //while(j > 0u)
       //{
       //  /* Zero is stored in the destination buffer */
       //  *pOut++ = 0.0f;

       //  /* Decrement the loop counter */
       //  j--;
       //}

     }
     else
     {
       /* Initialization of inputA pointer */
       pIn1 = pSrcB;

       /* Initialization of inputB pointer */
       pIn2 = pSrcA;

       /* srcBLen is always considered as shorter or equal to srcALen */
       j = srcBLen;
       srcBLen = srcALen;
       srcALen = j;

       /* CORR(x, y) = Reverse order(CORR(y, x)) */
       /* Hence set the destination pointer to point to the last output sample */
       pOut = pDst + ((srcALen + srcBLen) - 2u);

       /* Destination address modifier is set to -1 */
       inc = -1;

     }

     /* The function is internally
      * divided into three parts according to the number of multiplications that has to be
      * taken place between inputA samples and inputB samples. In the first part of the
      * algorithm, the multiplications increase by one for every iteration.
      * In the second part of the algorithm, srcBLen number of multiplications are done.
      * In the third part of the algorithm, the multiplications decrease by one
      * for every iteration.*/
     /* The algorithm is implemented in three stages.
      * The loop counters of each stage is initiated here. */
     blockSize1 = srcBLen - 1u;
     blockSize2 = srcALen - (srcBLen - 1u);
     blockSize3 = blockSize1;

     /* --------------------------
      * Initializations of stage1
      * -------------------------*/

     /* sum = x[0] * y[srcBlen - 1]
      * sum = x[0] * y[srcBlen-2] + x[1] * y[srcBlen - 1]
      * ....
      * sum = x[0] * y[0] + x[1] * y[1] +...+ x[srcBLen - 1] * y[srcBLen - 1]
      */

     /* In this stage the MAC operations are increased by 1 for every iteration.
        The count variable holds the number of MAC operations performed */
     count = 1u;

     /* Working pointer of inputA */
     px = pIn1;

     /* Working pointer of inputB */
     pSrc1 = pIn2 + (srcBLen - 1u);
     py = pSrc1;

     /* ------------------------
      * Stage1 process
      * ----------------------*/

     /* The first stage starts here */
     while(blockSize1 > 0u)
     {
       /* Accumulator is made zero for every iteration */
       sum = 0.0f;

       /* Apply loop unrolling and compute 4 MACs simultaneously. */
       k = count >> 2u;

       /* First part of the processing with loop unrolling.  Compute 4 MACs at a time.
        ** a second loop below computes MACs for the remaining 1 to 3 samples. */
       while(k > 0u)
       {
         /* x[0] * y[srcBLen - 4] */
         sum += *px++ * *py++;
         /* x[1] * y[srcBLen - 3] */
         sum += *px++ * *py++;
         /* x[2] * y[srcBLen - 2] */
         sum += *px++ * *py++;
         /* x[3] * y[srcBLen - 1] */
         sum += *px++ * *py++;

         /* Decrement the loop counter */
         k--;
       }

       /* If the count is not a multiple of 4, compute any remaining MACs here.
        ** No loop unrolling is used. */
       k = count % 0x4u;

       while(k > 0u)
       {
         /* Perform the multiply-accumulate */
         /* x[0] * y[srcBLen - 1] */
         sum += *px++ * *py++;

         /* Decrement the loop counter */
         k--;
       }

       /* Store the result in the accumulator in the destination buffer. */
       *pOut = sum;
       /* Destination pointer is updated according to the address modifier, inc */
       pOut += inc;

       /* Update the inputA and inputB pointers for next MAC calculation */
       py = pSrc1 - count;
       px = pIn1;

       /* Increment the MAC count */
       count++;

       /* Decrement the loop counter */
       blockSize1--;
     }

     /* --------------------------
      * Initializations of stage2
      * ------------------------*/

     /* sum = x[0] * y[0] + x[1] * y[1] +...+ x[srcBLen-1] * y[srcBLen-1]
      * sum = x[1] * y[0] + x[2] * y[1] +...+ x[srcBLen] * y[srcBLen-1]
      * ....
      * sum = x[srcALen-srcBLen-2] * y[0] + x[srcALen-srcBLen-1] * y[1] +...+ x[srcALen-1] * y[srcBLen-1]
      */

     /* Working pointer of inputA */
     px = pIn1;

     /* Working pointer of inputB */
     py = pIn2;

     /* count is index by which the pointer pIn1 to be incremented */
     count = 0u;

     /* -------------------
      * Stage2 process
      * ------------------*/

     /* Stage2 depends on srcBLen as in this stage srcBLen number of MACS are performed.
      * So, to loop unroll over blockSize2,
      * srcBLen should be greater than or equal to 4, to loop unroll the srcBLen loop */
     if(srcBLen >= 4u)
     {
       /* Loop unroll over blockSize2, by 4 */
       blkCnt = blockSize2 >> 2u;

       while(blkCnt > 0u)
       {
         /* Set all accumulators to zero */
         acc0 = 0.0f;
         acc1 = 0.0f;
         acc2 = 0.0f;
         acc3 = 0.0f;

         /* read x[0], x[1], x[2] samples */
         x0 = *(px++);
         x1 = *(px++);
         x2 = *(px++);

         /* Apply loop unrolling and compute 4 MACs simultaneously. */
         k = srcBLen >> 2u;

         /* First part of the processing with loop unrolling.  Compute 4 MACs at a time.
          ** a second loop below computes MACs for the remaining 1 to 3 samples. */
         do
         {
           /* Read y[0] sample */
           c0 = *(py++);

           /* Read x[3] sample */
           x3 = *(px++);

           /* Perform the multiply-accumulate */
           /* acc0 +=  x[0] * y[0] */
           acc0 += x0 * c0;
           /* acc1 +=  x[1] * y[0] */
           acc1 += x1 * c0;
           /* acc2 +=  x[2] * y[0] */
           acc2 += x2 * c0;
           /* acc3 +=  x[3] * y[0] */
           acc3 += x3 * c0;

           /* Read y[1] sample */
           c0 = *(py++);

           /* Read x[4] sample */
           x0 = *(px++);

           /* Perform the multiply-accumulate */
           /* acc0 +=  x[1] * y[1] */
           acc0 += x1 * c0;
           /* acc1 +=  x[2] * y[1] */
           acc1 += x2 * c0;
           /* acc2 +=  x[3] * y[1] */
           acc2 += x3 * c0;
           /* acc3 +=  x[4] * y[1] */
           acc3 += x0 * c0;

           /* Read y[2] sample */
           c0 = *(py++);

           /* Read x[5] sample */
           x1 = *(px++);

           /* Perform the multiply-accumulates */
           /* acc0 +=  x[2] * y[2] */
           acc0 += x2 * c0;
           /* acc1 +=  x[3] * y[2] */
           acc1 += x3 * c0;
           /* acc2 +=  x[4] * y[2] */
           acc2 += x0 * c0;
           /* acc3 +=  x[5] * y[2] */
           acc3 += x1 * c0;

           /* Read y[3] sample */
           c0 = *(py++);

           /* Read x[6] sample */
           x2 = *(px++);

           /* Perform the multiply-accumulates */
           /* acc0 +=  x[3] * y[3] */
           acc0 += x3 * c0;
           /* acc1 +=  x[4] * y[3] */
           acc1 += x0 * c0;
           /* acc2 +=  x[5] * y[3] */
           acc2 += x1 * c0;
           /* acc3 +=  x[6] * y[3] */
           acc3 += x2 * c0;


         } while(--k);

         /* If the srcBLen is not a multiple of 4, compute any remaining MACs here.
          ** No loop unrolling is used. */
         k = srcBLen % 0x4u;

         while(k > 0u)
         {
           /* Read y[4] sample */
           c0 = *(py++);

           /* Read x[7] sample */
           x3 = *(px++);

           /* Perform the multiply-accumulates */
           /* acc0 +=  x[4] * y[4] */
           acc0 += x0 * c0;
           /* acc1 +=  x[5] * y[4] */
           acc1 += x1 * c0;
           /* acc2 +=  x[6] * y[4] */
           acc2 += x2 * c0;
           /* acc3 +=  x[7] * y[4] */
           acc3 += x3 * c0;

           /* Reuse the present samples for the next MAC */
           x0 = x1;
           x1 = x2;
           x2 = x3;

           /* Decrement the loop counter */
           k--;
         }

         /* Store the result in the accumulator in the destination buffer. */
         *pOut = acc0;
         /* Destination pointer is updated according to the address modifier, inc */
         pOut += inc;

         *pOut = acc1;
         pOut += inc;

         *pOut = acc2;
         pOut += inc;

         *pOut = acc3;
         pOut += inc;

         /* Increment the pointer pIn1 index, count by 4 */
         count += 4u;

         /* Update the inputA and inputB pointers for next MAC calculation */
         px = pIn1 + count;
         py = pIn2;

         /* Decrement the loop counter */
         blkCnt--;
       }

       /* If the blockSize2 is not a multiple of 4, compute any remaining output samples here.
        ** No loop unrolling is used. */
       blkCnt = blockSize2 % 0x4u;

       while(blkCnt > 0u)
       {
         /* Accumulator is made zero for every iteration */
         sum = 0.0f;

         /* Apply loop unrolling and compute 4 MACs simultaneously. */
         k = srcBLen >> 2u;

         /* First part of the processing with loop unrolling.  Compute 4 MACs at a time.
          ** a second loop below computes MACs for the remaining 1 to 3 samples. */
         while(k > 0u)
         {
           /* Perform the multiply-accumulates */
           sum += *px++ * *py++;
           sum += *px++ * *py++;
           sum += *px++ * *py++;
           sum += *px++ * *py++;

           /* Decrement the loop counter */
           k--;
         }

         /* If the srcBLen is not a multiple of 4, compute any remaining MACs here.
          ** No loop unrolling is used. */
         k = srcBLen % 0x4u;

         while(k > 0u)
         {
           /* Perform the multiply-accumulate */
           sum += *px++ * *py++;

           /* Decrement the loop counter */
           k--;
         }

         /* Store the result in the accumulator in the destination buffer. */
         *pOut = sum;
         /* Destination pointer is updated according to the address modifier, inc */
         pOut += inc;

         /* Increment the pointer pIn1 index, count by 1 */
         count++;

         /* Update the inputA and inputB pointers for next MAC calculation */
         px = pIn1 + count;
         py = pIn2;

         /* Decrement the loop counter */
         blkCnt--;
       }
     }
     else
     {
       /* If the srcBLen is not a multiple of 4,
        * the blockSize2 loop cannot be unrolled by 4 */
       blkCnt = blockSize2;

       while(blkCnt > 0u)
       {
         /* Accumulator is made zero for every iteration */
         sum = 0.0f;

         /* Loop over srcBLen */
         k = srcBLen;

         while(k > 0u)
         {
           /* Perform the multiply-accumulate */
           sum += *px++ * *py++;

           /* Decrement the loop counter */
           k--;
         }

         /* Store the result in the accumulator in the destination buffer. */
         *pOut = sum;
         /* Destination pointer is updated according to the address modifier, inc */
         pOut += inc;

         /* Increment the pointer pIn1 index, count by 1 */
         count++;

         /* Update the inputA and inputB pointers for next MAC calculation */
         px = pIn1 + count;
         py = pIn2;

         /* Decrement the loop counter */
         blkCnt--;
       }
     }

     /* --------------------------
      * Initializations of stage3
      * -------------------------*/

     /* sum += x[srcALen-srcBLen+1] * y[0] + x[srcALen-srcBLen+2] * y[1] +...+ x[srcALen-1] * y[srcBLen-1]
      * sum += x[srcALen-srcBLen+2] * y[0] + x[srcALen-srcBLen+3] * y[1] +...+ x[srcALen-1] * y[srcBLen-1]
      * ....
      * sum +=  x[srcALen-2] * y[0] + x[srcALen-1] * y[1]
      * sum +=  x[srcALen-1] * y[0]
      */

     /* In this stage the MAC operations are decreased by 1 for every iteration.
        The count variable holds the number of MAC operations performed */
     count = srcBLen - 1u;

     /* Working pointer of inputA */
     pSrc1 = pIn1 + (srcALen - (srcBLen - 1u));
     px = pSrc1;

     /* Working pointer of inputB */
     py = pIn2;

     /* -------------------
      * Stage3 process
      * ------------------*/

     while(blockSize3 > 0u)
     {
       /* Accumulator is made zero for every iteration */
       sum = 0.0f;

       /* Apply loop unrolling and compute 4 MACs simultaneously. */
       k = count >> 2u;

       /* First part of the processing with loop unrolling.  Compute 4 MACs at a time.
        ** a second loop below computes MACs for the remaining 1 to 3 samples. */
       while(k > 0u)
       {
         /* Perform the multiply-accumulates */
         /* sum += x[srcALen - srcBLen + 4] * y[3] */
         sum += *px++ * *py++;
         /* sum += x[srcALen - srcBLen + 3] * y[2] */
         sum += *px++ * *py++;
         /* sum += x[srcALen - srcBLen + 2] * y[1] */
         sum += *px++ * *py++;
         /* sum += x[srcALen - srcBLen + 1] * y[0] */
         sum += *px++ * *py++;

         /* Decrement the loop counter */
         k--;
       }

       /* If the count is not a multiple of 4, compute any remaining MACs here.
        ** No loop unrolling is used. */
       k = count % 0x4u;

       while(k > 0u)
       {
         /* Perform the multiply-accumulates */
         sum += *px++ * *py++;

         /* Decrement the loop counter */
         k--;
       }

       /* Store the result in the accumulator in the destination buffer. */
       *pOut = sum;
       /* Destination pointer is updated according to the address modifier, inc */
       pOut += inc;

       /* Update the inputA and inputB pointers for next MAC calculation */
       px = ++pSrc1;
       py = pIn2;

       /* Decrement the MAC count */
       count--;

       /* Decrement the loop counter */
       blockSize3--;
     }

   #else

     /* Run the below code for Cortex-M0 */

     float32_t *pIn1 = pSrcA;                       /* inputA pointer */
     float32_t *pIn2 = pSrcB + (srcBLen - 1u);      /* inputB pointer */
     float32_t sum;                                 /* Accumulator */
     uint32_t i = 0u, j;                            /* loop counters */
     uint32_t inv = 0u;                             /* Reverse order flag */
     uint32_t tot = 0u;                             /* Length */

     /* The algorithm implementation is based on the lengths of the inputs. */
     /* srcB is always made to slide across srcA. */
     /* So srcBLen is always considered as shorter or equal to srcALen */
     /* But CORR(x, y) is reverse of CORR(y, x) */
     /* So, when srcBLen > srcALen, output pointer is made to point to the end of the output buffer */
     /* and a varaible, inv is set to 1 */
     /* If lengths are not equal then zero pad has to be done to  make the two
      * inputs of same length. But to improve the performance, we assume zeroes
      * in the output instead of zero padding either of the the inputs*/
     /* If srcALen > srcBLen, (srcALen - srcBLen) zeroes has to included in the
      * starting of the output buffer */
     /* If srcALen < srcBLen, (srcALen - srcBLen) zeroes has to included in the
      * ending of the output buffer */
     /* Once the zero padding is done the remaining of the output is calcualted
      * using convolution but with the shorter signal time shifted. */

     /* Calculate the length of the remaining sequence */
     tot = ((srcALen + srcBLen) - 2u);

     if(srcALen > srcBLen)
     {
       /* Calculating the number of zeros to be padded to the output */
       j = srcALen - srcBLen;

       /* Initialise the pointer after zero padding */
       pDst += j;
     }

     else if(srcALen < srcBLen)
     {
       /* Initialization to inputB pointer */
       pIn1 = pSrcB;

       /* Initialization to the end of inputA pointer */
       pIn2 = pSrcA + (srcALen - 1u);

       /* Initialisation of the pointer after zero padding */
       pDst = pDst + tot;

       /* Swapping the lengths */
       j = srcALen;
       srcALen = srcBLen;
       srcBLen = j;

       /* Setting the reverse flag */
       inv = 1;

     }

     /* Loop to calculate convolution for output length number of times */
     for (i = 0u; i <= tot; i++)
     {
       /* Initialize sum with zero to carry on MAC operations */
       sum = 0.0f;

       /* Loop to perform MAC operations according to convolution equation */
       for (j = 0u; j <= i; j++)
       {
         /* Check the array limitations */
         if((((i - j) < srcBLen) && (j < srcALen)))
         {
           /* z[i] += x[i-j] * y[j] */
           sum += pIn1[j] * pIn2[-((int32_t) i - j)];
         }
       }
       /* Store the output in the destination buffer */
       if(inv == 1)
         *pDst-- = sum;
       else
         *pDst++ = sum;
     }

   #endif /*   #ifndef ARM_MATH_CM0_FAMILY */

   }

   /**
    * @} end of Corr group
    */

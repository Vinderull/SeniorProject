/*!
 * @file
 *
 * @brief Frequency Detection framework
 *
 * @author ECE40X Senior Project
            Guitar Tuner
 * @author Ryan Dufour
 * @author Phil Robb
 *
 * @date Oct 2, 2018
 *
 * Board file for Lab 1, this is the code that gets flashed to board
 * this uses the example code provided by Hummels and the
 * ECE department.
 * we simply called our task functions in this code
 *This is implementing the arm_FIR functions on the board
 */

#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "ece486.h"
//#include <stdlib.h>
#include <stdio.h>
#include "arm_math.h"
#include <math.h>
//#include "UART.c"


#define nsamp 1000


extern FlagStatus KeyPressed;   // Use to detect button presses

int main(void)
{

  int i, n, j, maxIndex;
  float avg, dev, note, maxVal;
  float input[nsamp], output1[nsamp*2], output2[nsamp], output3[nsamp/2];
  static float sign=1.0;
  static int button_count = 0;
  uint16_t FFT_len = nsamp;
  char lcd_str[8];
  arm_rfft_fast_instance_f32 fftStruct;




  /*
   * Set up ADCs, DACs, GPIO, Clocks, DMAs, and Timer
   *
   * If your discovery board has been modified to support the external
   * HSE reference, use the (better quality crystal controlled) HSE
   * configuration.  If not, you can use the MSI reference, and things
   * should still work -- but your clocks will drift over time.
   *
   * The MSI (Medium speed internal) reference is the on-chip RC oscillator
   *
   * The HSE (High speed external) reference is an external clock, either
   * provided through the external connector, or (if your board is modified)
   * from the crystal reference source generated by the other processor
   * on the development board.
   */
  setblocksize(nsamp);
  initialize_ece486(FS_10K, MONO_IN, MONO_OUT, MSI_INTERNAL_RC);
  //UART2_Init();
  //initialize_ece486(FS_10K, MONO_IN, MONO_OUT, HSE_EXTERNAL_8MHz);

  /*
   * Allocate Required Memory
   */
  n = 1;
  avg = 1.0;

  //arm_rfft_fast_init_f32(&fftStruct, FFT_len);




   /*
   * Normally we avoid printf()... especially once we start actually
   * processing streaming samples.  This is here to illustrate the
   * use of printf for debugging programs.
   *
   * To see the printf output, connect to the ST-Link serial port.
   * Use: 115200 8N1
   */
  // printf("Starting execution using %d samples per input block.\n",nsamp);

  /*
   * Infinite Loop to process the data stream, "nsamp" samples at a time
   */
  while(1){





    /*
     * Ask for a block of ADC samples to be put into the working buffer
     *   getblock() will wait here until the input buffer is filled...  On return
     *   we work on the new data buffer... then return here to wait for
     *   the next block
     */

    /*
     * signal processing code to calculate the required output buffers
     */



    DIGITAL_IO_SET(); 	// Use a scope on PD0 to measure execution time
    getblock(input);

    //putblock(input);

    //this will also keep track of how many blocks collected
    //since decimating we will need #D blocks until FFT is full

    arm_correlate_f32(input, nsamp, input, nsamp, output1);
   //arm_rfft_fast_f32(&fftStruct, input, output1, 0);
   arm_mean_f32(output1, nsamp*2, &avg);




  /* subtract mean */
   for(i=0; i<nsamp*2; i++){
     output1[i] -= avg;

     /*zero out negative correlations */
     //if(output1[i]<0) output1[i] = 0;
   }


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
    for(i=0; i<nsamp*2; i++){
     if ((output2[i] < avg + (2*dev)) output2[i] = 0;
    }


   /* peak detection */
      for(i = 1; i<nsamp-1; i++ ){

         if(((output2[i] - output2[i-1])>0) && ((output2[i+1]-output2[i])<0)){
           n = i;
         }

         else if((output2[i] - output2[i-1])>0) continue;

         else if((output2[i+1] - output2[i]) < 0) continue;
      }

      note = 10000.0/((float) n);



   //arm_cmplx_mag_squared_f32(output1, output2, 512);

    //arm_rfft_fast_f32(fftStruct, output2, output3, 1);


  for(i=0; i<nsamp; i++){


    printf("%f, ", note);

  }

    //snprintf((char *)buffer, BufferSize, "TEST: %f\t\r\n", input[i]);
    //n += sprintf((char *)buffer + n, "Equivalent Voltage = %f\r\n", a);
    //USART_Write(USART2, buffer, n);










    DIGITAL_IO_RESET();	// (falling edge....  done processing data )






    if (KeyPressed) {
      KeyPressed = RESET;

      /*
       * On each press, modify the LCD display, and toggle an LED
       * (LED4=red, LED5=green) (Red is used to show error conditions)
       *
       * Don't be surprised when these cause a Sample Overrun error,
       * depending on your sample rate.
       */
      button_count++;
      sprintf(lcd_str, "BTN %2d", button_count);
      BSP_LCD_GLASS_DisplayString( (uint8_t *)lcd_str);
      BSP_LED_Toggle(LED5);
    }

    //dummy while to get only one output
    while(1);
  }
}

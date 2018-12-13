
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_hal.h"
#include "adc.h"
#include "opamp.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "ADCsrc.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config_MSI(void);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
#define SAMPLE_SIZE 1000
volatile uint32_t adc[SAMPLE_SIZE];
volatile uint32_t buffer[SAMPLE_SIZE];
volatile uint32_t Buffer_Ping[SAMPLE_SIZE];
volatile uint32_t Buffer_Pong[SAMPLE_SIZE];
volatile uint32_t *pReadyWrite = Buffer_Ping;
volatile uint32_t *pReadyProcess = Buffer_Pong;
volatile uint32_t ADC_DMA_DONE = 0;
float vsense = 3.3/4095;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  char Message[40] = "thing\n\r";
  float frequency = 0;
  float samples[SAMPLE_SIZE];

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
//  MX_TIM4_Init();
  TIM4_Init();
  MX_USART2_UART_Init();
  MX_OPAMP2_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //HAL_TIM_Base_Init(&htim4);
  //HAL_TIM_Base_Start(&htim4);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *) pReadyProcess, SAMPLE_SIZE);

  /*transmit sring over usart2 */
  HAL_UART_Transmit(&huart2, (uint8_t *) &Message, 15, 0xFFF);
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_ADC;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 8;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the main internal regulator output voltage
    */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */


void SystemClock_Config_MSI(void)
{
      RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
     RCC_OscInitTypeDef RCC_OscInitStruct = {0};

      /* MSI is enabled after System reset, activate PLL with MSI as source */
     RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
     RCC_OscInitStruct.MSIState = RCC_MSI_ON;
      RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_8;
       RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;

      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
       RCC_OscInitStruct.PLL.PLLM = 2;
       RCC_OscInitStruct.PLL.PLLN = 20;
       RCC_OscInitStruct.PLL.PLLR = 2;
       RCC_OscInitStruct.PLL.PLLP = 7;
       RCC_OscInitStruct.PLL.PLLQ = 5;
      if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
     {
        /* Initialization Error */
       while(1);
       }

   /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
    clocks dividers */
   RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
   {
   /* Initialization Error */
    while(1);
  }
 }




void DMA_Init(int arg)
{
//arg number of conversions
//uint32_t ADC_Results[arg];


/* Enable DMA1 Clock */
RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

//Enable DMA channel
DMA1_Channel1->CCR &= ~DMA_CCR_EN;

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
DMA1_Channel1->CMAR =  (uint32_t) pReadyProcess;

//transfer complete interrupt enable
DMA1_Channel1->CCR |= DMA_CCR_TCIE;

//disable half complete
DMA1_Channel1->CCR &= ~DMA_CCR_HTIE;
DMA1_Channel1->CCR |= DMA_CCR_HTIE;

// configure ADC for DMA in circular mode
//ADC1->CFGR |= ADC_CFGR_DMACFG;
//DMA enable?
//ADC1->CFGR |= ADC_CFGR_DMAEN;

//set DMA interrupt priority
NVIC_SetPriority(DMA1_Channel1_IRQn, 1);

//enable DMA INTERRUPT
NVIC_EnableIRQ(DMA1_Channel1_IRQn);


//DMA Channel selection
//map DMA channel 1 to ADC1
//0000: Channel 1 mapped to ADC1
DMA1_CSELR->CSELR &= ~DMA_CSELR_C1S;

//Enable DMA channel
DMA1_Channel1->CCR |= DMA_CCR_EN;

}


void DMA1_Channel1_IRQHandler(void){

if((DMA1->ISR & DMA_ISR_TCIF1) == DMA_ISR_TCIF1){

  //write 1 to clear flag
  DMA1->IFCR |= DMA_IFCR_CTCIF1;

  if (pReadyWrite == Buffer_Ping){
    pReadyWrite = Buffer_Pong;
    pReadyProcess = Buffer_Ping;
  }
  else{
    pReadyWrite = Buffer_Ping;
    pReadyProcess = Buffer_Pong;
  }

  //DMA memory address
  DMA1_Channel1->CMAR = (uint32_t) pReadyWrite;
  ADC_DMA_DONE = 1;
 }


//clear flags
DMA1->IFCR |= (DMA_IFCR_CHTIF1 | DMA_IFCR_CGIF1 | DMA_IFCR_CTEIF1);
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

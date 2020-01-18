/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ADCsrc.h"
#include "PA5_Timer.h"
#include <stdlib.h>
#include "Yin.h"
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void DMA_Init(uint16_t arg);
void SystemClock_Config_MSI(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define SAMPLE_SIZE 4096
#define FREQUENCY_CORRECTION 2

//volatile uint32_t Buffer_Ping[SAMPLE_SIZE];
//volatile uint32_t Buffer_Pong[SAMPLE_SIZE];
//volatile uint32_t *pReadyWrite = Buffer_Ping;
//volatile uint32_t *pReadyProcess = Buffer_Pong;

/*trying out 16 bit, ADC resolution is only 12-bit to begin with */
/* DMA data bus may be 32-bit, but setting transfer to HALFWORD seems to work */
volatile uint16_t Buffer_Ping[SAMPLE_SIZE];
volatile uint16_t Buffer_Pong[SAMPLE_SIZE];
volatile uint16_t *pReadyWrite = Buffer_Ping;
volatile uint16_t *pReadyProcess = Buffer_Pong;
volatile uint8_t ADC_DMA_DONE = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  char Message[40] = "thing\n\r";
  uint16_t mask = 0XFFFF;
  uint16_t i;
  float frequency = 0;
  int beat = 0;
  //float samples[SAMPLE_SIZE];
  Yin yin;

  /* USER CODE END 1 */


  /* MCU Configuration--------------------------------------------------------*/

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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM4_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  DMA_Init(SAMPLE_SIZE);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //HAL_TIM_Base_Init(&htim2);
  //HAL_TIM_Base_Start(&htim2);
  //HAL_TIM_Base_Init(&htim4);
  HAL_TIM_Base_Start(&htim4);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_ADC_Start_DMA(&hadc1, (uint16_t *) pReadyProcess, SAMPLE_SIZE);

  /*transmit sring over usart2 */
  HAL_UART_Transmit(&huart2, (uint8_t *) &Message, 15, 0xFFF);
  while (1)
  {



  while(ADC_DMA_DONE == 0);

  /*Initialize Yin struct and get pitch. Yin_init dynamically allocates memory*/
  /* and as a result the buffer needs to be freed after each calculation */
  Yin_init(&yin, SAMPLE_SIZE, YIN_DEFAULT_THRESHOLD);
  frequency = Yin_getPitch(&yin, pReadyProcess);
  free(yin.yinBuffer);

  /*beat calc */
  frequency = 79.3;
  beat = calcBeat(frequency, 82.41);

/*
  HAL_Delay(100);
  if(pwm_value == 0) step = 100;
  if(pwm_value == 2000) step = -100;
  pwm_value += step;
*/
  //set_PWM(beat);

  sprintf(Message, "The Note is %f\n\r", beat);
  /*transmit sring over usart2 */
  HAL_UART_Transmit(&huart2, (uint8_t *) &Message, 40, 0xFFF);

  /*Scale Frequency by scaling factor */
  //frequency /= FREQUENCY_CORRECTION;

  ADC_DMA_DONE = 0;



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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
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
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */




void DMA_Init(uint16_t arg)
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
  * @retval None
  */
void Error_Handler(void)
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
void assert_failed(char *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

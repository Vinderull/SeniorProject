//DMA Init


void DMA_Init(int arg)
{
//arg number of conversions
uint16_t ADC_Results[arg];

/* Enable DMA1 Clock */
RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

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
DMA1_Channel1->CMAR = (uint32_t) pReadyProcess;

//transfer complete interrupt enable
DMA1_Channel1->CCR |= DMA_CCR_TCIE;

//enable DMA INTERRUPT
NVIC_EnableIRQ(DMA1_Channel1_IRQn);


//DMA Channel selection
//map DMA channel 1 to ADC1
//0000: Channel 1 mapped to ADC1
DMA1_CSELR->CSELR &= ~DMA_CSELR_C1S;

//Enable DMA channel
DMA1_Channel1->CCR |= DMA_CCR_EN;




}

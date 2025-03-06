################################################################################
Author: armando.rivero@supsi.ch
Date: 30.09.2022
################################################################################
This example trnasfer data from the memory to the GPIO peripheral using the timer1 





/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#undef TIM1_ARR
#define TIM1_ARR 18-1
/* USER CODE END PD */

!!!!!! I M P O R T A N T !!!!! 
The "MX_DMA_Init()" function should always be initialized before the timers

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  

THIS APPLICATION GENERATES A WAVEFORM USING GPIOs

  /* USER CODE BEGIN 2 */
  int memSize = 16;
  uint32_t memToGpioData[memSize];
   for(int i=0;i<memSize;i++)
     memToGpioData[i]=0;

   memToGpioData[ 0] = 0x00000001;
   memToGpioData[ 2] = 0x00010020;
   memToGpioData[ 9] = 0x00200040;
   memToGpioData[13] = 0x00400000;


   // DMA, circular memory-to-peripheral mode, full word (32 bit) transfer
   HAL_DMA_Start(&hdma_tim1_up,  (uint32_t)memToGpioData, (uint32_t)&(GPIOA->BSRR), memSize);
   HAL_TIM_Base_Start(&htim1);
   HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1);
   TIM1->DIER |= (1 << 8);   // set UDE bit (update dma request enable)


!!!!!! I M P O R T A N T !!!!! 
The register "TIM1->DIER |= (1 << 8)" should be set like this to enable the transfer to the DMA

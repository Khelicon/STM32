
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
#include "stm32l0xx_hal.h"
#include "hss_lowpower.h"
#include "shtx.h"
#include "FloatToString.h"
#include "hss_oled_ssd1306.h"
#include "hss_stm32_oled_fonts.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef hlpuart1;

RTC_HandleTypeDef hrtc;


#define RXBUFFERSIZE    10
uint8_t aRxBuffer[1];    /* UART  */
uint8_t Rx_Buffer[RXBUFFERSIZE];    /* UART  */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void System_Init(void);
void System_ReInit(void);
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_RTC_Init(void);
static void MX_I2C1_Init(void);

/* USER CODE BEGIN PFP */
/* Global variables -----------------------------------------------*/
  char  outBuff[50];
	char  response_flag;
	float tempC = 0;
	float rHum = 0;
	int   count = 0;
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

void OLED_Clear()
{
  TM_SSD1306_GotoXY(0, 0);
  TM_SSD1306_UpdateScreen();
  TM_SSD1306_Fill(SSD1306_COLOR_BLACK);  
  TM_SSD1306_UpdateScreen();
}

void OLED_Startup()
{
   OLED_Clear();

   TM_SSD1306_GotoXY(10, 10);
   TM_SSD1306_Puts("OLED & SHT30", &TM_Font_7x10 , SSD1306_COLOR_WHITE); 
   TM_SSD1306_GotoXY(40, 40);
   TM_SSD1306_Puts("I2C", &TM_Font_7x10 , SSD1306_COLOR_WHITE);  
   TM_SSD1306_UpdateScreen();

}

/* USER CODE END 0 */

void OLED_Display_SHTx()
{
   char dispayString[32];
    
   OLED_Clear();

   TM_SSD1306_GotoXY(10, 0);
   TM_SSD1306_Puts("OLED & SHT30", &TM_Font_7x10 , SSD1306_COLOR_WHITE);
   
   // Temperature
   memset(dispayString, 0, sizeof(dispayString));
   dtostrf(tempC, 4, 2, dispayString);
   TM_SSD1306_GotoXY(0, 20);
   TM_SSD1306_Puts("Temp: ", &TM_Font_7x10 , SSD1306_COLOR_WHITE);
   TM_SSD1306_GotoXY(40, 20);
   TM_SSD1306_Puts(dispayString, &TM_Font_7x10 , SSD1306_COLOR_WHITE);

   

   // Humidity
   memset(dispayString, 0, sizeof(dispayString));
   dtostrf(rHum, 4, 2, dispayString);
   TM_SSD1306_GotoXY(0, 40);
   TM_SSD1306_Puts("RH: ", &TM_Font_7x10 , SSD1306_COLOR_WHITE);
   TM_SSD1306_GotoXY(40, 40);
   TM_SSD1306_Puts(dispayString, &TM_Font_7x10 , SSD1306_COLOR_WHITE);
   TM_SSD1306_GotoXY(80, 40);
   TM_SSD1306_Puts("%", &TM_Font_7x10 , SSD1306_COLOR_WHITE);
 
   TM_SSD1306_UpdateScreen();
}

/**
  * @brief  The application entry point.
  *
  * @retval None
  */

int main(void)
{
  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
   System_Init();
   OLED_Startup();
   HAL_Delay(2000);
  /* USER CODE BEGIN 2 */
 
  HSS_Serial_text("Starting System!\r\n");
  for(int i = 0; i < 10; i++)
  {
    //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,  1);
    HAL_Delay(100);
  }

  /* USER CODE END 2 */
  /*__HAL_UART_ENABLE_IT(&hlpuart1,UART_IT_RXNE); */
  HAL_UART_Receive_IT(&hlpuart1, (uint8_t *)aRxBuffer, 1);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */
  
  /* USER CODE END WHILE */
    //HAL_UART_Transmit(&hlpuart1, "Going to StopMode!\r\n", sizeof("Going to StopMode!\r\n"), 20);
    HSS_Serial_text("Going to StopMode!\r\n");
    HSS_Serial_text("Send uart msg to wake");
    HSS_Serial_text(" up!\r\n");
    
    /* Wakup from Uart Receive interrupt or RTC(if enabled) */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
    // Turn off the OLED
    OLED_Clear();
    // Go to Standby Mode for 5 Seconds
    HSS_Lowpower_Stop(5000);
    // Reinit the System
    System_ReInit();

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
    HSS_Serial_text("Wakeup from RTC \r\n");
  
    if(SHTx_Read(&hi2c1, &tempC, &rHum))
    {
      // Send Humidity over UART terminal //
      dtostrf(tempC, 4, 2, outBuff);
      HSS_Serial_text("Temp:");
      HSS_Serial_text(outBuff );
     
      // Send Humidity over UART terminal //
      dtostrf(rHum, 4, 2, outBuff);
      HSS_Serial_text(", RH:" );
      HSS_Serial_text(outBuff );
      HSS_Serial_newLine();

      OLED_Display_SHTx();
      
    }
    else
    {
      HSS_Serial_text("SHTx failed\r\n" );
    }
      
    // just for fun!, keep the display for some time before going to sleep
    HAL_Delay(3000);

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}


//Interrupt callback routine
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == LPUART1)
  {
    HAL_UART_Transmit(&hlpuart1, &aRxBuffer[0], sizeof(aRxBuffer[0]), 10);    
    /*__HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_RXNE); */
    
  }
  HAL_UART_Receive_IT(&hlpuart1, (uint8_t *)aRxBuffer, 1);
}

void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
{
   // send '12345678901234567890123' to wakup 
  HSS_Serial_text("UARTEx Wakeup!\r\n");
 	  
	HAL_UART_Receive_IT(&huart, (uint8_t *)aRxBuffer, 1);	//activate UART receive interrupt every time
}


void System_Init()
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_RTC_Init();  
  MX_LPUART1_UART_Init(); 
   
  TM_SSD1306_Init();
  SHTx_Init(0x45);
  
}

void System_ReInit()
{
   /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  // Deactivate RTC wakeUp
  HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_LPUART1_UART_Init();
  
  MX_I2C1_Init(); 
  SHTx_Init(0x45);

  //TM_SSD1306_Init();
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

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /**Configure LSE Drive Capability 
   * 
  */
   HAL_PWR_EnableBkUpAccess();
   __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
/*
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
  */

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

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_RTC;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_HSI;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  /**Configure the Systick interrupt time*/
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  /*Configure the Systick*/
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x0010061A;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Analogue filter 
    */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Digital filter 
    */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* LPUART1 init function */
static void MX_LPUART1_UART_Init(void)
{

  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 9600;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* RTC init function */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;
  RTC_AlarmTypeDef sAlarm;

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

    /**Initialize RTC Only 
    */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 0x7c;
  hrtc.Init.SynchPrediv = 0x127;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initialize RTC and set the Time and Date 
    */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Enable the Alarm A 
    */
  sAlarm.AlarmTime.Hours = 0x0;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x0;
  sAlarm.AlarmTime.SubSeconds = 0x0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 0x1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Enable the Alarm B 
    */
  sAlarm.AlarmDateWeekDay = 0x1;
  sAlarm.Alarm = RTC_ALARM_B;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Enable the WakeUp 
    */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


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

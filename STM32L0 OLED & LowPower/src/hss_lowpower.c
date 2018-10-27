


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_hal.h"
 
#include "string.h"

#include "hss_lowpower.h"

extern UART_HandleTypeDef hlpuart1;
extern RTC_HandleTypeDef hrtc;

/* The objective is to create a Stop Mode switch with automatic wake-up after 500ms, 
   on Serial event and on external GPIO event (external interrupt). */

void HSS_Lowpower_Stop(unsigned int sleeptime)
{
  // Configure RTC to wake up after TimeToWakeup (e.g 500ms) 
  uint32_t _time = (((uint32_t)sleeptime) * 2314) / 1000;
  HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, _time, RTC_WAKEUPCLOCK_RTCCLK_DIV16);

  __HAL_RCC_PWR_CLK_ENABLE(); // Enable Power Control clock
  HAL_PWREx_EnableUltraLowPower(); // Ultra low power mode
  HAL_PWREx_EnableFastWakeUp(); // Fast wake-up for ultra low power mode

  // Disable Unused Gpios
  // HSS_GPIO_Disable(); // Disable GPIOs based on configuration

  // Configure LPUART for Wake-up
  // make sure that no UART transfer is on-going
  while(__HAL_UART_GET_FLAG(&hlpuart1, USART_ISR_BUSY) == SET);
  // make sure that UART is ready to receive
  while(__HAL_UART_GET_FLAG(&hlpuart1, USART_ISR_REACK) == RESET);

  UART_WakeUpTypeDef wakeup;
  wakeup.WakeUpEvent=UART_WAKEUP_ON_STARTBIT; // UART_WAKEUP_ON_READDATA_NONEMPTY
  HAL_UARTEx_StopModeWakeUpSourceConfig(&hlpuart1,wakeup);
  __HAL_UART_ENABLE_IT(&hlpuart1, UART_IT_WUF);
  HAL_UARTEx_EnableStopMode(&hlpuart1);

  // GPIO Wake up is configured by CubeMx config and keeping the GPIO activated


  // Switch to STOPMode
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
}


/* Includes ------------------------------------------------------------------*/
 
#include "stm32l0xx_hal.h"
#include "hss_serialport.h" 
#include "string.h"

extern UART_HandleTypeDef hlpuart1;
/* Private variables ---------------------------------------------------------*/
#define serial    hlpuart1
unsigned int timeout = 20;
void HSS_Serial_begin(long baudrate)
{
   //MX_USART2_UART_Init(baudrate);
}

void HSS_Serial_text(char *str)
{
  int len = strlen(str);
 
  /* Send data using UART followed by second uart transmit command with 3 argument with 'sizeof("")',
     Somehow Receive Interrupt stop working when in 3 argument using len = strlen(str) is sent. 
     I will invesigate further and fix this issue (probably string termination issue with null). 
     This is workround for now. */

  HAL_UART_Transmit(&serial, (uint8_t*)str, len, timeout);
  HAL_UART_Transmit(&serial, (uint8_t*)"\0", sizeof("\0"), timeout);

  //HAL_UART_Transmit(&hlpuart1, "PowerMode Uart!\r\n", sizeof("PowerMode Uart!\r\n"), 20);
    
}

void HSS_Serial_newLine()
{
  HAL_UART_Transmit(&serial, "\r\n", sizeof("\r\n"), timeout);
}


void HSS_Serial_char(char chr)
{}
void HSS_Serial_float(double fvalue)
{}
void HSS_Serial_int(int ivalue)
{}
void HSS_Serial_uint(unsigned iValue)
{}
 
 



  // HAL_UART_Transmit(&huart2, "Hello World\r\n", sizeof("Hello World\r\n"), 10);
  // HAL_UART_Transmit(&hlpuart1, "Hello LPUART\r\n", sizeof("Hello LPUART\r\n"), 10);
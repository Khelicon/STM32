
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HS_SERIALPORT_H__
#define __HS_SERIALPORT_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "string.h"
#include "usart.h"
#include "stdbool.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/* USER CODE END Private defines */


#ifdef __cplusplus
 extern "C" {
#endif

typedef enum {
	HS_UART_1 = 0x00, /*!< Everything OK */
	HS_UART_2,     
  HS_UART_3,  
  HS_UART_LowPower
} HS_UART_PORT_t;


 
HAL_StatusTypeDef HS_Serial_Begin(HS_UART_PORT_t uartType, long baud);
void HS_Serial_Text(char *str);
void HS_Serial_Char(char chr);
void HS_Serial_Float(double fvalue);
void HS_Serial_Int(int ivalue);
void HS_Serial_Uint(unsigned iValue);
void HS_Serial_NewLine(void);

char HS_LPUART1_Check_Message(char *message);

void HS_Serial_Handle_IT(char rxbyte);
void HS_Serial_RX_Enable_IT(HS_UART_PORT_t port);



#ifdef __cplusplus
}
#endif

#endif /* __HS_SERIALPORT_H__ */
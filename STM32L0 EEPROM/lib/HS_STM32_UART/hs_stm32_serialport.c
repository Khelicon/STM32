
/* Includes ------------------------------------------------------------------*/ 
#include "hs_stm32_serialport.h"  

/* Defines -------------------------------------------------------------------*/
extern  UART_HandleTypeDef hlpuart1;
#define serial    hlpuart1
unsigned int timeout = 20;


/* Private variables ---------------------------------------------------------*/
#define END_FLAG '$'
#define START_FLAG '@'

short uartCounter = 0;
short BUFFER_COUNT= 0;
const uint8_t  BUFFER_SIZE = 32;
char  BUFFER_RX_Read[32];
bool  RX_FLAG = 0; 
bool  Recv_Start_FLAG = 0;
  

char aRxBuffer[1];

//------------------------------------------------------------------------------
// Function Name :  HS_Serial_RX_Enable_IT()
// Description   :  Enable Receive Interrupt!
// Input         :  Uart peripherals: LPUART or UART
//------------------------------------------------------------------------------
void HS_Serial_RX_Enable_IT(HS_UART_PORT_t port)
{
   HAL_UART_Receive_IT(&hlpuart1, (uint8_t *)aRxBuffer, 1);
}

//------------------------------------------------------------------------------
// Function Name :  HS_Serial_Begin()
// Description   :  UART initialization process,
// Input         :  Uart peripherals & baudrate
//------------------------------------------------------------------------------
HAL_StatusTypeDef HS_Serial_Begin(HS_UART_PORT_t uartType, long baud)
{
  switch(uartType)
  {
    case 0: return HAL_ERROR; break;
    case 1: return HAL_ERROR; break;
    case 2: return HAL_ERROR; break;
    case 3: return MX_LPUART1_UART_Init(baud); break;
    default: HAL_ERROR;  // if unknown UART port defined!
  }  

  // clear buffer!
  memset(aRxBuffer, 0, sizeof(aRxBuffer));
  memset(BUFFER_RX_Read, 0, sizeof(BUFFER_RX_Read));
}

//------------------------------------------------------------------------------
// Function Name :  HS_Serial_Text()
// Description   :  Emulating arduino style Serial port for debugging
// Input         :  Text string
//------------------------------------------------------------------------------
void HS_Serial_Text(char *str)
{
  int timer = 20;
  int len = strlen(str);
  if (len > 15) timer = 50;
  HAL_UART_Transmit(&serial, (uint8_t*)str, len, timer);
  
  // sending null byte end of string, or somebody gonna have bad time!
  HAL_UART_Transmit(&serial, (uint8_t*)"\0", sizeof("\0"), timeout);
}

//------------------------------------------------------------------------------
// Function Name :  HS_Serial_NewLine()
// Description   :  send new line over serial terminal
// Input         :  NONE
//------------------------------------------------------------------------------
void HS_Serial_NewLine()
{
  HAL_UART_Transmit(&serial, (uint8_t*)"\r\n", sizeof("\r\n"), timeout);
}

//------------------------------------------------------------------------------
// Function Name :  HS_Serial_Char()
// Description   :  Send 'char' over uart port
// Input         :  
//------------------------------------------------------------------------------
void HS_Serial_Char(char chr)
{
  char buff[7];
  sprintf(buff, "%d", chr);
  HS_Serial_Text(buff);
}

void HS_Serial_Float(double fvalue)
{}

void HS_Serial_Int(int ivalue)
{}

void HS_Serial_Uint(unsigned iValue)
{}

//------------------------------------------------------------------------------
// Function Name :  HS_LPUART1_Check_Message()
// Description   :  When UART interrupt complete, User can check for message
// Input         :  pointer to buffer for holding data 
//------------------------------------------------------------------------------
char HS_LPUART1_Check_Message(char *message)
{	   
		char result = 0;	   
		if(RX_FLAG)
		{
			 /* Clear the RX Flag */
			 RX_FLAG = false;

			 /* Pass the address of store message */			  
			 strcpy(message, BUFFER_RX_Read); 
			 result = 1;
		}		 
		return result;
}

//------------------------------------------------------------------------------
// Function Name :  HS_Serial_Handle_IT()
// Description   :  when uart interupt occurs, data is processed here
// Input         :  
//------------------------------------------------------------------------------
void HS_Serial_Handle_IT(char rxbyte)
{
	 char recv;
	 recv = rxbyte;

   if(Recv_Start_FLAG) {
      if((recv == END_FLAG) || (BUFFER_COUNT >= (BUFFER_SIZE-1))) {        
        /* add null for string termination */
        BUFFER_RX_Read[BUFFER_COUNT] = '\0';	 
        BUFFER_COUNT = 0;     
        RX_FLAG = true;   
        Recv_Start_FLAG = false;
      }
      else {
        BUFFER_RX_Read[BUFFER_COUNT++] = recv;        
      }
   }    

   if ((recv == START_FLAG) && (Recv_Start_FLAG != true)) Recv_Start_FLAG = true;

}

/* ===================================== Interrupt callback routine =============================================*/
//------------------------------------------------------------------------------
// Function Name :  HAL_UART_RxCpltCallback()
// Description   :  when UART receive interupt occurs,this is callback called from receive interrupt
// Input         :  
//------------------------------------------------------------------------------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

  if(huart->Instance == LPUART1)
  {
    HS_Serial_Handle_IT(aRxBuffer[0]);
    /* Reinit Receive interrupt */
    HAL_UART_Receive_IT(&huart->Instance, (uint8_t *)aRxBuffer, 1);
  }
  
}

//------------------------------------------------------------------------------
// Function Name :  HAL_UARTEx_WakeupCallback()
// Description   :  Uart wakeup occurs from sleep
// Input         :  
//------------------------------------------------------------------------------
void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
{
   // send something like '12345678901234567890123' to wakeup 
   HS_Serial_Text("UARTEx Wakeup!\r\n"); 	  
	 //HAL_UART_Receive_IT(&huart->Instance, (uint8_t *)aRxBuffer, 1);	//activate UART receive interrupt every time
}
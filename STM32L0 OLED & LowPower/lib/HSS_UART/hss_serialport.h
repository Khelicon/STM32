
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HSS_SERIALPORT_H__
#define __HSS_SERIALPORT_H__

/* Includes ------------------------------------------------------------------*/

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


 
 
void HSS_Serial_text(char *str);
void HSS_Serial_char(char chr);
void HSS_Serial_float(double fvalue);
void HSS_Serial_int(int ivalue);
void HSS_Serial_uint(unsigned iValue);

void HSS_Serial_newLine(void);



#ifdef __cplusplus
}
#endif

#endif /* __HSS_SERIALPORT_H__ */
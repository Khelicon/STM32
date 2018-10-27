
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HSS_OLED_I2C_WRAPPER_H__
#define __HSS_OLED_I2C_WRAPPER_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
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

/**
 * @brief  I2C result enumeration
 */
typedef enum {
	TM_I2C_Result_Ok = 0x00, /*!< Everything OK */
	TM_I2C_Result_Error      /*!< An error has occurred */
} TM_I2C_Result_t;


 
 TM_I2C_Result_t TM_I2C_IsDeviceConnected(I2C_TypeDef* I2Cx, uint8_t address);
 


#ifdef __cplusplus
}
#endif

#endif /* __HSS_OLED_I2C_WRAPPER_H__ */
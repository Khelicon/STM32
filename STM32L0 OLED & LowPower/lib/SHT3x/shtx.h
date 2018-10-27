


/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HSS_SHTX_H__
#define __HSS_SHTX_H__


#ifdef __cplusplus
 extern "C" {
#endif


void SHTx_Init(uint8_t addr);
uint8_t SHTx_Read(I2C_HandleTypeDef *hi2c, float *temperature, float *humidity);

#ifdef __cplusplus
}
#endif

#endif /* __HSS_SHTX_H__ */

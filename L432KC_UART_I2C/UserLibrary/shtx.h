
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SHTX_H__
#define __SHTX_H__

void SHTx_Init(uint8_t addr);
uint8_t SHTx_Read(I2C_HandleTypeDef *hi2c, float *temperature, float *humidity);
#endif /* __SHTX_H__ */

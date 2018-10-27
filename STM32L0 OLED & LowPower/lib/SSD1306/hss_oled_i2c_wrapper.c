
#include "hss_oled_i2c_wrapper.h"

extern I2C_HandleTypeDef hi2c1;

#define I2C_Handle &hi2c1

/* Timeout value */
#define I2C_TIMEOUT_VALUE              1000

/* Handle values for I2C */
#ifdef I2C1
static I2C_HandleTypeDef I2C1Handle = {I2C1};
#endif
#ifdef I2C2
static I2C_HandleTypeDef I2C2Handle = {I2C2};
#endif
#ifdef I2C3
static I2C_HandleTypeDef I2C3Handle = {I2C3};
#endif
#ifdef I2C4
static I2C_HandleTypeDef I2C4Handle = {I2C4};
#endif

 

I2C_HandleTypeDef* TM_I2C_GetHandle(I2C_TypeDef* I2Cx) {
  
    return I2C_Handle;
	 
}

TM_I2C_Result_t TM_I2C_IsDeviceConnected(I2C_TypeDef* I2Cx, uint8_t device_address) 
{
    
    I2C_HandleTypeDef* Handle = TM_I2C_GetHandle(I2Cx);
	
	/* Check if device is ready for communication */
	if (HAL_I2C_IsDeviceReady(Handle, device_address, 2, 5) != HAL_OK) {
		/* Return error */
		return TM_I2C_Result_Error;
	}	
	/* Return OK */
	return TM_I2C_Result_Ok;
}

TM_I2C_Result_t TM_I2C_Write(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t register_address, uint8_t data) 
{
	uint8_t d[2];
	I2C_HandleTypeDef* Handle = TM_I2C_GetHandle(I2Cx);
		
	/* Format array to send */
	d[0] = register_address;
	d[1] = data;
	
	/* Try to transmit via I2C */
	if (HAL_I2C_Master_Transmit(Handle, (uint16_t)device_address, (uint8_t *)d, 2, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return TM_I2C_Result_Error;
	} 
	
	/* Return OK */
	return TM_I2C_Result_Ok;
}

TM_I2C_Result_t TM_I2C_WriteMulti(I2C_TypeDef* I2Cx, uint8_t device_address, uint16_t register_address, uint8_t* data, uint16_t count) {
	I2C_HandleTypeDef* Handle = TM_I2C_GetHandle(I2Cx);

	/* Try to transmit via I2C */
	if (HAL_I2C_Mem_Write(Handle, device_address, register_address, register_address > 0xFF ? I2C_MEMADD_SIZE_16BIT : I2C_MEMADD_SIZE_8BIT, data, count, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return TM_I2C_Result_Error;
	}
	
	/* Return OK */
	return TM_I2C_Result_Ok;
}
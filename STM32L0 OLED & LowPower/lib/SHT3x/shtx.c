
/* Includes ------------------------------------------------------------------*/
 
#include "shtx.h"
#include "hss_serialport.h"
#include "string.h"

/* Private variables ---------------------------------------------------------*/
#define SHTx_ERROR	0
#define SHTx_OK		1
uint8_t _address = 0x45;

static uint8_t CMD_MEASURE_HPM[]     = { 0x2C, 0x06 };

extern I2C_HandleTypeDef hi2c1;
/*
 * Initialize the SHTx I2C Module
 */
void SHTx_Init(uint8_t addr)
{
  /* Initialize I2Cx if not done in main() */

  /* Asssign the addres of SHTx module */
  _address = addr;
}


/*
 * Read Temperature and Humidity, return 1 if success, return 0 if fails
 */
uint8_t SHTx_Read(I2C_HandleTypeDef *hi2c, float *temperature, float *humidity)
{
	uint8_t  buffer[6];
	 
	float cTemp, rH;
	//long wait_counter = 0;

	 
	HSS_Serial_text("Reading Temp & Humidity");
	HSS_Serial_newLine();

	/* Check if device is ready for communication */
	if (HAL_I2C_IsDeviceReady(hi2c, (_address << 1), 2, 5) != HAL_OK) 
	{
		HSS_Serial_text("SHTx Device Fails");
	    HSS_Serial_newLine();
		return SHTx_ERROR;
	}	

	if(HAL_I2C_Master_Transmit(hi2c, (_address << 1), CMD_MEASURE_HPM, 2, 100)  != HAL_OK)
	{
		HSS_Serial_text("SHTx Error1");
	    HSS_Serial_newLine();
		return SHTx_ERROR;
	}

    
	// while(wait_counter++ <= 10000) {}

	if(HAL_I2C_Master_Receive(hi2c, (_address << 1), buffer, 6, 100) != HAL_OK) {
		HSS_Serial_text("SHTx Error2 ");
	    HSS_Serial_newLine();
		return SHTx_ERROR;
	}

	// Convert the data
	cTemp = ((((buffer[0] * 256.0) + buffer[1]) * 175) / 65535.0) - 45;
	// fTemp = (cTemp * 1.8) + 32;
	rH = ((((buffer[3] * 256.0) + buffer[4]) * 100) / 65535.0);

    *temperature = cTemp;
	*humidity    = rH;
    

	return (uint8_t) SHTx_OK;

}

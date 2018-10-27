
#include "stm32l0xx_hal.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "hs_stm32_24xx1025.h"



extern I2C_HandleTypeDef hi2c1;

static int DevAddress;
uint16_t currentaddress = 0x0000;

//------------------------------------------------------------------------------
// Function Name :  HS_EEPROM_24LC1025_Write()
// Description   :  Write single byte to given memory address
// Input         :  
//------------------------------------------------------------------------------
void HS_EEPROM_24LC1025_Init(int i2caddress) 
{
   DevAddress = i2caddress;
}

//------------------------------------------------------------------------------
// Function Name :  HS_EEPROM_24LC1025_Write
// Description   :  Write single byte to given memory address
// Input         :  memory addres and data
//------------------------------------------------------------------------------
void HS_EEPROM_24LC1025_Write(int address, char data) 
{
    /* Check if device is ready for communication */
	if (HAL_I2C_IsDeviceReady(&hi2c1, DevAddress, 2, 5) == HAL_OK) 
	{
        if(HAL_I2C_Mem_Write(&hi2c1, DevAddress, address, I2C_MEMADD_SIZE_16BIT, &data, 1, 100) != HAL_OK)
        {}	 
	}
}

//------------------------------------------------------------------------------
// Function Name :  HS_EEPROM_24LC1025_Read
// Description   :  Read single byte from given memory address
// Input         :  memory address to read byte
// Return        :  retun single byte from given memory address
//------------------------------------------------------------------------------
char HS_EEPROM_24LC1025_Read(int addr) 
{    
  char data;
   if (HAL_I2C_IsDeviceReady(&hi2c1, DevAddress, 2, 5) == HAL_OK) 
   {
        if(HAL_I2C_Mem_Read(&hi2c1, DevAddress, addr, I2C_MEMADD_SIZE_16BIT, &data, 1, 100) == HAL_OK)
        {
            return data;
	    }
        else return 4;
   }
	else return 3;
}

//------------------------------------------------------------------------------
// Function Name :  HS_EEPROM_24LC1025_WriteArray
// Description   :  Write multiple bytes array to starting from given address
// Input         :  starting memory address and pointer to data buffer and size of data to write 
//------------------------------------------------------------------------------
void HS_EEPROM_24LC1025_WriteArray(int addr, char *data, char size) 
{ 
   if (HAL_I2C_IsDeviceReady(&hi2c1, DevAddress, 2, 5) == HAL_OK) 
   {
        if(HAL_I2C_Mem_Write(&hi2c1, DevAddress, addr, I2C_MEMADD_SIZE_16BIT, data, size, 100) != HAL_OK)
        {	 	
        }  
   } 
}

//------------------------------------------------------------------------------
// Function Name :  HS_EEPROM_24LC1025_ReadArray
// Description   :  Read multiple data from starting from given memory address.
// Input         :  address of memory and pointer to data buffer and size of data to read 
//------------------------------------------------------------------------------
void HS_EEPROM_24LC1025_ReadArray(int addr, char *data, char size) 
{
    if (HAL_I2C_IsDeviceReady(&hi2c1, DevAddress, 2, 5) == HAL_OK) 
   {
        if(HAL_I2C_Mem_Read(&hi2c1, DevAddress, addr, I2C_MEMADD_SIZE_16BIT, data, size, 100) == HAL_OK)
        {		 
        } 
   }
}

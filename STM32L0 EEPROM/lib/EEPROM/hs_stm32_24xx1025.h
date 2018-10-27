


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EE_24XX1025_H
#define __EE_24XX1025_H

#ifdef __cplusplus
 extern "C" {
#endif


#define EE24XX1025_100MHZ         100000
#define EE24XX1025_400MHZ         400000

#define EE24XX1025_WRITE          0b00000000
#define EE24XX1025_READ           0b00000001
#define EE24XX1025_A0             0b00000010
#define EE24XX1025_A1             0b00000100
#define EE24XX1025_BLOCK0         0b00000000
#define EE24XX1025_BLOCK1         0b00001000
#define EE24XX1025_CONTROLCODE    0b10100000

#define _XTAL_FREQ                24000000




/* Includes ------------------------------------------------------------------*/

  //void eeprom_24lc1025_write(char addr_i2c, int addr, char data);
  void HS_EEPROM_24LC1025_Init(int i2caddress);
  void HS_EEPROM_24LC1025_Write(int addr, char data);
  void HS_EEPROM_24LC1025_WriteArray(int addr, char *data, char size);

  char HS_EEPROM_24LC1025_Read(int addr);
  void HS_EEPROM_24LC1025_ReadArray(int addr, char *data, char size);


#ifdef __cplusplus
}
#endif
#endif /*__EE_24XX1025_H */
    
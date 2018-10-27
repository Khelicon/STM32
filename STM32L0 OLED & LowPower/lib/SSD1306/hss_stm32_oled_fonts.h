 
#include "stm32l0xx_hal.h"

#ifndef TM_FONTS_H
#define TM_FONTS_H 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup TM_FONTS_Typedefs
 * @brief    Library Typedefs
 * @{
 */

/**
 * @brief  Font structure used on my LCD libraries
 */
typedef struct {
	uint8_t FontWidth;    /*!< Font width in pixels */
	uint8_t FontHeight;   /*!< Font height in pixels */
	const uint16_t *data; /*!< Pointer to data font data array */
} TM_FONT_t;

/** 
 * @brief  String width and height in unit of pixels 
 */
typedef struct {
	uint16_t Width;       /*!< String width in units of pixels */
	uint16_t Height;      /*!< String height in units of pixels */
} TM_FONT_SIZE_t;

/**
 * @}
 */

/**
 * @defgroup TM_FONTS_FontVariables
 * @brief    Library font variables
 * @{
 */

/**
 * @brief  7 x 10 pixels font size structure 
 */
extern TM_FONT_t TM_Font_7x10;

/**
 * @brief  11 x 18 pixels font size structure 
 */
extern TM_FONT_t TM_Font_11x18;

/**
 * @brief  16 x 26 pixels font size structure 
 */
extern TM_FONT_t TM_Font_16x26;

/**
 * @}
 */
 
/**
 * @defgroup TM_FONTS_Functions
 * @brief    Library functions
 * @{
 */

/**
 * @brief  Calculates string length and height in units of pixels depending on string and font used
 * @param  *str: String to be checked for length and height
 * @param  *SizeStruct: Pointer to empty @ref TM_FONTS_SIZE_t structure where informations will be saved
 * @param  *Font: Pointer to @ref TM_FontDef_t font used for calculations
 * @retval Pointer to string used for length and height
 */
char* TM_FONT_GetStringSize(char* str, TM_FONT_SIZE_t* SizeStruct, TM_FONT_t* Font);



/* C++ detection */
#ifdef __cplusplus
}
#endif

 
#endif
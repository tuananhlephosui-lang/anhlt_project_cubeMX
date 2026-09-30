#ifndef MYLCDLIB_H
#define MYLCDLIB_H
#include <stdint.h>
#include "stm32f1xx_hal.h"

//#define LCD_D0_Pin GPIO_PIN_0
//#define LCD_D0_GPIO_Port GPIOA
//#define LCD_D1_Pin GPIO_PIN_1
//#define LCD_D1_GPIO_Port GPIOA
//#define LCD_D2_Pin GPIO_PIN_2
//#define LCD_D2_GPIO_Port GPIOA
//#define LCD_RS_Pin GPIO_PIN_0
//#define LCD_RS_GPIO_Port GPIOB
//#define LCD_RW_Pin GPIO_PIN_1
//#define LCD_RW_GPIO_Port GPIOB
//#define LCD_E_Pin GPIO_PIN_10
//#define LCD_E_GPIO_Port GPIOB
//#define LCD_D3_Pin GPIO_PIN_8
//#define LCD_D3_GPIO_Port GPIOA
//#define LCD_D4_Pin GPIO_PIN_9
//#define LCD_D4_GPIO_Port GPIOA
//#define LCD_D5_Pin GPIO_PIN_10
//#define LCD_D5_GPIO_Port GPIOA
//#define LCD_D6_Pin GPIO_PIN_11
//#define LCD_D6_GPIO_Port GPIOA
//#define LCD_D7_Pin GPIO_PIN_12
//#define LCD_D7_GPIO_Port GPIOA

#define MDATA 0x01
#define MCMD	0x00

typedef struct {
	GPIO_TypeDef 	*PORT;
	uint16_t			PIN;
}PORT_PIN;

typedef struct {
	PORT_PIN	D0;
	PORT_PIN	D1;
	PORT_PIN	D2;
	PORT_PIN	D3;
	PORT_PIN	D4;
	PORT_PIN	D5;
	PORT_PIN	D6;
	PORT_PIN	D7;
	PORT_PIN	RS;
	PORT_PIN	RW;
	PORT_PIN	En;
}LCD_Config_t;


void LCD_init(const LCD_Config_t *lcd);
void LCD_Write_Byte(const LCD_Config_t *lcd, const uint8_t* data, uint8_t mode);
void LCD_Write_data(const LCD_Config_t *lcd, uint8_t data);
void LCD_Write_cmd(const LCD_Config_t *lcd, uint8_t cmd);
void LCD_Print(const LCD_Config_t *lcd, char *str);
void LCD_SetCursor(const LCD_Config_t *lcd, uint8_t row, uint8_t col);


#endif // MYLCDLIB_H
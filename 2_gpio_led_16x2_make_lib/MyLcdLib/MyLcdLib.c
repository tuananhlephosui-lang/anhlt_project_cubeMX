#include "myLcdLib.h"

void LCD_init(const LCD_Config_t *lcd) {
	HAL_Delay(50);
	
	LCD_Write_cmd(lcd, 0x30);
	HAL_Delay(5);
	LCD_Write_cmd(lcd, 0x30);
	HAL_Delay(1);
	LCD_Write_cmd(lcd, 0x30);
	HAL_Delay(1);
	
	LCD_Write_cmd(lcd, 0x38); // Function Set
	HAL_Delay(5);
	LCD_Write_cmd(lcd, 0x0C); // Make cusor invisible
	HAL_Delay(5);
	LCD_Write_cmd(lcd, 0x01);	// clear screen
	HAL_Delay(5);
	LCD_Write_cmd(lcd, 0x06);	// entry mode
	HAL_Delay(5);
}

void LCD_Write_Byte(const LCD_Config_t *lcd, const uint8_t*  data, uint8_t mode) {
	HAL_GPIO_WritePin(lcd->RW.PORT, lcd->RW.PIN, 0); // write mode
	
	if(mode == 0x01){
		// data
		HAL_GPIO_WritePin(lcd->RS.PORT, lcd->RS.PIN, 1);
	} else if(mode == 0x00) {
		// cmd
		HAL_GPIO_WritePin(lcd->RS.PORT, lcd->RS.PIN, 0);
	} else {
		// do nothing
	}
	
	HAL_GPIO_WritePin(lcd->D0.PORT, lcd->D0.PIN, ((*data) & 0x01) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->D1.PORT, lcd->D1.PIN, ((*data) & 0x02) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->D2.PORT, lcd->D2.PIN, ((*data) & 0x04) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->D3.PORT, lcd->D3.PIN, ((*data) & 0x08) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->D4.PORT, lcd->D4.PIN, ((*data) & 0x10) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->D5.PORT, lcd->D5.PIN, ((*data) & 0x20) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->D6.PORT, lcd->D6.PIN, ((*data) & 0x40) ? 1 : 0);
	HAL_GPIO_WritePin(lcd->D7.PORT, lcd->D7.PIN, ((*data) & 0x80) ? 1 : 0);
	
	HAL_GPIO_WritePin(lcd->En.PORT, lcd->En.PIN, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(lcd->En.PORT, lcd->En.PIN, 0);
	HAL_Delay(1);
}

void LCD_Write_data(const LCD_Config_t *lcd, uint8_t data) {
	LCD_Write_Byte(lcd, &data, 0x01);
}

void LCD_Write_cmd(const LCD_Config_t *lcd, uint8_t cmd) {
	LCD_Write_Byte(lcd, &cmd, 0x00);
}

void LCD_Print(const LCD_Config_t *lcd, char *str) {
	while(*str) {
		LCD_Write_data(lcd, *str++);
	}
}

void LCD_SetCursor(const LCD_Config_t *lcd, uint8_t row, uint8_t col) {
    uint8_t address;
    if (row == 0) {
			address = 0x80 + col;        // dong 1: dia chi 0x00 + col (them bit 1 ? DB7 -> 0x80)
    } else {
        address = 0xC0 + col;        // dong 2: dia chi 0x40 + col (0x80 + 0x40 = 0xC0)
    }
    LCD_Write_cmd(lcd, address);
}
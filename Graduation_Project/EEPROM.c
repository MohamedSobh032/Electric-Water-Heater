/*
 * EEPROM.c
 *
 * Created: 6/2/2023 2:54:28 PM
 *  Author: Abd-Allah Ahmad Aref
 */ 


#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "STD_Macros.h"
#include "I2C.h"


void Write_EEPROM(char data,char page , char line)
{
	char address=(0xA<<4) | (page<<1);
	I2C_Start(address);
	I2C_Write(line);
	I2C_Write(data);
	I2C_Stop();
}

char Read_EEPROM(char page , char line)
{
	char data=0;
	char address=(0xA<<4) | (page<<1);
	I2C_Start(address);
	I2C_Write(line);
	I2C_Repeated_Start(address | 0x01);
	data =I2C_Read_Ack();
	I2C_Stop();
	return data;
}
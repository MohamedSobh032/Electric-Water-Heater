/*
 * EEPROM.h
 *
 * Created: 6/2/2023 2:54:41 PM
 *  Author: Abd-Allah Ahmad Aref
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

void Write_EEPROM(char data,char page , char line);
char Read_EEPROM(char page , char line);



#endif /* EEPROM_H_ */
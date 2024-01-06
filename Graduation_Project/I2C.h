/*
 * I2C.h
 *
 * Created: 1/28/2023 9:32:35 PM
 *  Author: AMIT
 */ 


#ifndef I2C_H_
#define I2C_H_
#define SCL_CLK 10000
//SCL frequency =  (CPU CLK frequency)/(16+2(TWBR)*4^TWPS )
// f/sf =16+2(TWBR)*4^TWPS
//f/sf-16 =2(TWBR)*4^TWPS
//(f/sf-16)/4^TWPS*2 = TWBR
/* Define bit rate */
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))

void I2C_Stop();
char I2C_Read_Nack();
char I2C_Read_Ack();

char I2C_Write(char data);
char I2C_Repeated_Start(char read_address) ;
char I2C_Start(char address);
void I2C_Init()	;





#endif /* I2C_H_ */
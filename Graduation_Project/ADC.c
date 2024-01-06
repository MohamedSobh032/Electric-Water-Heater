/*
 * ADC.c
 *
 * Created: 5/6/2023 3:15:33 PM
 *  Author: Abd-Allah Ahmad Aref
 */ 
#define F_CPU 1000000ul
#include <avr/io.h>
#include "STD_Macros.h"
#include "ADC.h"
#include <util/delay.h>

void ADC_INIT()
{
	SETBIT(ADMUX,REFS0);
	SETBIT(ADCSRA,ADEN);
	SETBIT(ADCSRA,ADPS0);
}
int ADC_Read(int Channel)
{
	int x =0;
	if (Channel<8)
	{
		ADMUX =(ADMUX &0xE0) | Channel;
		SETBIT(ADCSRA,ADSC);
		while(READBIT(ADCSRA,ADIF)==0){;}
		_delay_us(10);
		x= (int)ADCL+(int) ADCH *256 ;
	}
	return x;
}
/*
 * Graduation_Project.c
 *
 * Created: 7/15/2023 3:29:32 PM
 * Author : Abd-Allah Ahmad Aref
 */ 


#define  F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "STD_Macros.h"
#include "Timer0.h"
#include "Timer2.h"
#include "ADC.h"
#include "I2C.h"
#include "STD_Macros.h"
#include "Interrupt.h"
#include "EEPROM.h"
#include "SS.h"

int main(void)
{
	ADC_INIT();
	INT1_INIT();
	//////////////////////////////////////////////////////////////////////////
	//SET PINS FOR INPUT
	CLEARBIT(DDRD,0);
	CLEARBIT(DDRD,1);
	//SET PORT FOR OUTPUT
	SETBIT(DDRC,7);
	
	//////////////////////////////////////////////////////////////////////////
	ReqTemp = 60;				//The initial temperature is 60
	Mode = 2;					//HEATING OR COOLING
	SettingMode = 0;			//IF 1 Setting Mode is active
	//////////////////////////////////////////////////////////////////////////
	
	Write_EEPROM(60,1,1);	//Write Required temp to EEPROM (initially to 60) 
	
	//////////////////////////////////////////////////////////////////////////
    while (1) 
    {
		if(Systemflag)
		{
			writeSS(ActualTemp);
			if(READBIT(PIND,1)==0 || READBIT(PIND,0)==0)
			{
				SettingMode=1;
				while(READBIT(PIND,1)==0 || READBIT(PIND,0)==0){;}
				count_t2=0;
				Timer2_INIT(5000);
				while(count_t2<MaxCount_t2) //5 seconds wait
				{
					if(READBIT(PIND,0)==0)
					{
						while(READBIT(PIND,0)==0){;}
						ReqTemp-=5;
						if(ReqTemp<35)
						{
							ReqTemp=35;
						}
						count_t2=0;
					}
					if(READBIT(PIND,1)==0)
					{
						while(READBIT(PIND,1)==0){;}
						ReqTemp+=5;
						if(ReqTemp>75)
						{
							ReqTemp=75;
						}
						count_t2=0;
					}
					writeSS(ReqTemp);
					
				}
				CLEARBIT(TCCR2,CS01);  //Stops Timer2
				SettingMode=0;
			}
			if(ActualTemp<ReqTemp-5)
			{
				Mode=1; //Activate Heater
			}
			if(ActualTemp>ReqTemp+5)
			{
				Mode=0; //Activate Cooler
			}
			if(Mode==1)
			{
				SETBIT(PORTB,7);
				CLEARBIT(PORTB,6);
			}
			if(Mode==0)
			{
				SETBIT(PORTB,6);
				CLEARBIT(PORTB,7);
			}
		}
		
    }
}




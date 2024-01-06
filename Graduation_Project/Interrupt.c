/*
 * Interrupt.c
 *
 * Created: 5/5/2023 4:11:04 PM
 *  Author: Abd-Allah Ahmad Aref
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "STD_Macros.h"
#include "Interrupt.h"
#include "Timer0.h"
#include "SS.h"
#include "EEPROM.h"
volatile char Systemflag=0; //FLAG to control the whole system
volatile int ReqTemp=60; //Required temperature set by user

void INT1_INIT()
{
	SETBIT(MCUCR,ISC11);
	SETBIT(MCUCR,ISC10);
	sei();
	SETBIT(GICR,INT1);
	CLEARBIT(DDRD,3);
}

void INT0_INIT()
{
	sei();
	SETBIT(MCUCR,ISC01);
	SETBIT(GICR,INT0);
	CLEARBIT(DDRD,2);
}

ISR(INT0_vect)
{
	//
}

ISR(INT1_vect)
{
	Systemflag^=1;
	if(Systemflag)
	{
		TIMER0_INIT(100); //START Timer0
		ReqTemp=(int)Read_EEPROM(1,1);  //Read required temperature from EEPROM
		SS_Init(); //START 7-Seg Display
		// START HEATER and COOLER (LEDS)
		SETBIT(PORTC,7); 
		SETBIT(DDRB,6);
		SETBIT(DDRB,7);
	}
	else
	{
		Write_EEPROM(ReqTemp,1,1); //Write the last required temperature to EEPROM
		SS_Deinit(); //STOP 7-Seg Display
		//STOP TIMERS
		CLEARBIT(TCCR0,CS01);
		CLEARBIT(TCCR0,CS00);
		// STOP HEATER and COOLER (LEDS)
		CLEARBIT(PORTC,7);
		CLEARBIT(DDRB,6);
		CLEARBIT(DDRB,7);
	}
}
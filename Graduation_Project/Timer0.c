/*
 * Timer.c
 *
 * Created: 5/12/2023 3:23:29 PM
 *  Author: Mohamed
 */ 

#define F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "STD_Macros.h"
#include "Timer0.h"
#include "ADC.h"
#include "SS.h"

volatile int counter = 0;
volatile int MaxCount = 0;
volatile int PreloadValue = 0;
int MeasuredTemp[10] = {60, 60, 60, 60, 60, 60, 60, 60, 60, 60};
int ArrCount = 0;
int SumTemp = 600;
volatile int ActualTemp=60;
volatile char Mode;
volatile char SettingMode;

void TIMER0_INIT(int DesiredTime)
{	
	sei();						//Global Interrupt EN
	SETBIT(TCCR0,CS00);
	SETBIT(TCCR0,CS01);			//Prescalar = 8
	CLEARBIT(TCCR0,CS02);
	SETBIT(TIMSK,TOIE0);		//Interrupt EN
	
	int cal = 0;
	cal = NUMOVFT0(DesiredTime);
	MaxCount = cal/10;
	PreloadValue = PRELOAD(cal);
}


ISR(TIMER0_OVF_vect)
{
	counter++;
	if (counter > MaxCount)
	{
		//Counting 100 ms
		counter = 0;
		
		SumTemp -= MeasuredTemp[ArrCount];							//Delete the most early temperature measured
		MeasuredTemp[ArrCount] = (500.0 * ADC_Read(0)) / 1024.0;	//Measure the new temperature
		SumTemp += MeasuredTemp[ArrCount];							//Adds the new temperature
		ActualTemp = SumTemp / 10;									//Gets the average of all measured temperature
		ArrCount++;
		
		//Counting 1 Second
		
		if (ArrCount >= 10)											//If the timer counts 1 second
		{
			ArrCount = 0;											//reset the arrayCount
			if (Mode==1)											//Heating element on
			{
				TOGGLEBIT(PORTC,7);
				_delay_ms(100);
				TOGGLEBIT(PORTC,7);
			}
			if (SettingMode)										//Temp Setting mode
			{
				SS_Deinit();
				_delay_ms(100);
				SS_Init();
			}
		}
	}
}


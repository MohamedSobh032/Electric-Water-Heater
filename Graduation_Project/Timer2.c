/*
 * Timer2.c
 *
 * Created: 5/19/2023 3:57:24 PM
 *  Author: Abd-Allah Ahmad Aref
 */ 
#define  F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include "STD_Macros.h"
#include "Timer2.h"
#include <util/delay.h>
volatile int count_t2=0;
volatile int MaxCount_t2=0;
volatile int Preload_t2=0;

void Timer2_INIT(int DesiredT)
{
	SETBIT(TCCR2,CS01);
	SETBIT(TIMSK,TOIE2);
	sei(); //global interrupt enable
	int cal=NOVF(DesiredT);
	Preload_t2=PRELOAD_t2(cal);
	MaxCount_t2=cal/10;
}



ISR(TIMER2_OVF_vect)
{
	count_t2++;
}

/*
 * SS.c
 *
 * Created: 4/15/2023 1:56:38 PM
 *  Author: Mohamed
 */ 
#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "STD_Macros.h"
#include "SS.h"


void SS_Init()
{
	DDRA |= 0xf0;
	DDRC |= 0x3c;
}

void SS_Deinit()							//To allow blinking and shutting down
{
	DDRA &= 0x0f;
	DDRC &= 0xc3;
}

void writeSS(int x)
{
	SS_WriteMostSig(x/10);					//write big number on portA -> (x/10)
	SS_WriteLeastSig(x%10);					//write small number on portC -> (x%10)
}
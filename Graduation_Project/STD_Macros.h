/*
 * STD_Macros.h
 *
 * Created: 4/14/2023 1:57:52 PM
 *  Author: Abd-Allah Ahmad Aref
 */ 


#ifndef STD_MACROS_H_INCLUDED
#define STD_MACROS_H_INCLUDED

#define SETBIT(Reg,bit)		Reg=Reg | (1<<bit)
#define CLEARBIT(Reg,bit)	Reg=Reg & (~(1<<bit))
#define TOGGLEBIT(Reg,bit)	Reg=Reg ^ (1<<bit)
#define READBIT(Reg,bit)	((Reg>>bit) & 1)


#endif 
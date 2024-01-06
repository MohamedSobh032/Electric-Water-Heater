/*
 * IncFile1.h
 *
 * Created: 4/14/2023 1:53:15 PM
 *  Author: Mohamed
 */ 


#ifndef SS_H_
#define SS_H_


#define SS_WriteMostSig(x)			PORTA = (x<<4) | (PORTA & 0x0f)
#define SS_WriteLeastSig(x)			PORTC = (x<<2) | (PORTC & 0xc3)

void SS_Init();
void SS_Deinit();
void writeSS(int x);


#endif /* SS_H_ */
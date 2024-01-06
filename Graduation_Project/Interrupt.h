/*
 * Interrupt.h
 *
 * Created: 5/5/2023 4:11:45 PM
 *  Author: Abd-Allah Ahmad Aref
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_
extern volatile char Systemflag;
extern volatile int ReqTemp;

void INT0_INIT();
void INT1_INIT();



#endif /* INTERRUPT_H_ */
/*
 * Timer.h
 *
 * Created: 5/12/2023 3:23:15 PM
 *  Author: Mohamed
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

void TIMER0_INIT(int DesiredTime);

#define PS 64
#define CTCvalue 200

#define NUMOVFT0(DT)	(((unsigned long long) DT )*F_CPU*10ul)/(256ul * ((unsigned long long) PS )*1000ul)
#define PRELOAD(x)		(((10-(x%10))*256)/10)

#define NUMOVFT0CTC(DT)	(((unsigned long long) DT )*F_CPU*10ul)/(CTCvalue * 1ul * ((unsigned long long) PS )*1000ul)
#define PRELOADCTC(x)		(((10-(x%10))*CTCvalue)/10)


extern volatile int counter;
extern volatile int MaxCount;
extern volatile int PreloadValue;
extern volatile int ActualTemp;
extern volatile char Mode;
extern volatile char SettingMode;
#endif /* TIMER0_H_ */
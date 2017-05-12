#ifndef  __ENCODER_TIMER_Z
#define  __ENCODER_TIMER_Z
#include "encoder_timer.h"
class EncoderTimerZ:public EncoderTimer
{
	Gpio *pinZ;
	Exti exit;
	void reset() 
	{
		setPos(0);
	}
public:
	
	EncoderTimerZ(TIM_TypeDef *TIMx, Gpio *Gpioz) :
		EncoderTimer(TIMx),
		pinZ(Gpioz),
		exit(pinZ,EXTI_Trigger_Rising)
	{
	}
	void begin()
	{
		EncoderTimer::begin();
		pinZ->mode(INPUT);
	}
	void exitSetup()
	{
		exit.begin();
		exit.attach(this,&EncoderTimerZ::reset);
	    exit.interrupt(ENABLE);
	}
};
#endif
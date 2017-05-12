#include "tb6612.h"
Motor::Motor(Gpio *pwmA, Gpio *Ain1, Gpio *Ain2, Gpio *stby, Gpio *pwmB, Gpio *Bin1, Gpio *Bin2) :
	pwma(pwmA), ain1x(Ain1), ain2x(Ain2), stbyx(stby), pwmb(pwmB), bin1x(Bin1), bin2x(Bin2),
	mode(0), pct1(500),pct2(500) 
{

}

void Motor::begin()
{
	pwma.begin(72000, 500);
	pwma.set_oc_polarity(0);
	ain1x->mode(OUTPUT_PP);
	ain2x->mode(OUTPUT_PP);
	pwmb.begin(72000, 500);
	pwmb.set_oc_polarity(0);
	bin1x->mode(OUTPUT_PP);
	bin2x->mode(OUTPUT_PP);

	stbyx->mode(OUTPUT_PP);
	stbyx->set();//STBY脚置1使得电机一直可以转
}

void Motor::setMode(int mode)
{
	if (mode == Stop)
	{
		ain1x->reset(); ain2x->reset();
		bin1x->reset(); bin2x->reset();
	}
	if (mode == Forward)
	{
		ain1x->reset(); ain2x->set();
		bin1x->reset(); bin2x->set();
	}
	if (mode == BackOff)
	{
		ain1x->set(); ain2x->reset();
		bin1x->set(); bin2x->reset();
	}
}

void Motor::setMotorPct(int pct1,int pct2)
{
	pwma.set_duty(pct1);
	pwmb.set_duty(pct2);
}

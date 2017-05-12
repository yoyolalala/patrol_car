#include "ebox.h"
typedef enum
{
	Stop,
	Forward,
	BackOff
}motorModel;
class Motor
{
	int mode;
	int pct1,pct2;
	Pwm pwma;
	Gpio *ain1x;
	Gpio *ain2x;
	Gpio *stbyx;
	Pwm pwmb;
	Gpio *bin1x;
	Gpio *bin2x;
public:
	Motor(Gpio *pwmA, Gpio *Ain1, Gpio *Ain2, Gpio *stby, Gpio *pwmB, Gpio *Bin1, Gpio *Bin2);
	void begin();
	void setMode(int mode);
	void setMotorPct(int pct1,int pct2);
};
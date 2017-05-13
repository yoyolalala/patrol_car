#include "ebox.h"
#include "parallel_gpio.h"
ParallelGpio led;
class PointLed
{
	uint8_t writeValue;
public:
	void begin()
	{
		led.bit[0] = &PB3; 
		led.bit[1] = &PB4; 
		led.bit[2] = &PB5;
		led.bit[3] = &PB6;
		led.bit[4] = &PB7;
		led.bit[5] = &PA11;
		led.bit[6] = &PA12;
		led.bit[7] = &PA15;
		led.mode(AIN);
	}
	void write(uint8_t writeValue)
	{
	  led.write(writeValue);
	}
};
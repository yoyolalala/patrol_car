#include "ebox.h"
#include "ebox_analog.h"
#define l1 PA0
#define l2 PA1
#define l3 PA2
#define l4 PA3
#define r1 PA4
#define r2 PA5 
#define r3 PA6
#define r4 PA7//将红外从左至右定义为l1,l2,l3,l4,r1,r2,r3,r4
class Scan
{
public:
	int compare(uint16_t v)
	{
		if (v >= 1500)
			return 0;//线外
		else return 1;
	}
	uint8_t scan_init()
	{
		r1.mode(AIN); r2.mode(AIN); r3.mode(AIN); r4.mode(AIN); l1.mode(AIN); l2.mode(AIN); l3.mode(AIN); l4.mode(AIN);//模拟输入模式
		uint16_t r11 = analog_read_voltage(&r1);//单位为mv 比较时与1500比较
		uint16_t r21 = analog_read_voltage(&r2);
		uint16_t r31 = analog_read_voltage(&r3);
		uint16_t r41 = analog_read_voltage(&r4);
		uint16_t l11 = analog_read_voltage(&l1);
		uint16_t l21 = analog_read_voltage(&l2);
		uint16_t l31 = analog_read_voltage(&l3);
		uint16_t l41 = analog_read_voltage(&l4);//读出电压值 3300为参考
		uint8_t scanvalue = 0x00;
		int a = this->compare(r11);
		int b = this->compare(r21);
		int c = this->compare(r31);
		int d = this->compare(r41);
		int e = this->compare(l11);
		int f = this->compare(l21);
		int g = this->compare(l31);
		int h = this->compare(l41);
		scanvalue += a << 8; scanvalue += b << 7; scanvalue += c << 6; scanvalue += d << 5; scanvalue += e << 4; scanvalue += f << 3; scanvalue += g << 2; scanvalue += h << 1;
		return scanvalue;
	}
};
#include "ebox.h"
#include "ebox_in_capture.h"
#include "PID.hpp"
#include "ebox_pwm.h"
#include "scan.hpp"
#include "led.h"
#define refresh_interval 0.01
const int pct = 300;//定义电机直行时转速
int mode;
greg::PID pid; Led led(&PC13,1);
InCapture encoder1(&PA10); //默认全部1为左侧电机和编码器 2为右侧电机和编码器
InCapture encoder2(&PB10);
Scan scan; 
uint8_t scanvalue = scan.scan_init();//读取八位红外扫描数据 直行状态为00011000
Pwm pwm1(&PB9); Pwm pwm2(&PB8);
float d = encoder1.get_wave_peroid() - encoder2.get_wave_peroid();
typedef enum
{	
    left1,
	left2,
	left3,
    straight,
	right1,
	right2,
	right3
}Car_Mode_Typedef;
void setMotorspeed(int a, int b)
{
	pwm1.set_duty(a);
	pwm2.set_duty(b);
}
void mode0()//最左两个红外在线上的情况 应右轮调大占空比PB8
{
	pid.refresh(d);
	pid.setDesiredPoint(200);//假设此时目标左轮周期比右轮小200
	pid.setWeights(4, 3, 6);
}
void setMode(Car_Mode_Typedef m)
{
	mode = m;
}
void setup()//pwm 编码器 PID的初始化
{
	pid.setRefreshInterval(refresh_interval);
	pid.setOutputLowerLimit(0);
	pid.setOutputUpperLimit(1500);
	led.begin();
	ebox_init();//系统初始化	
	pwm1.set_oc_polarity(0);//比较匹配后输出低电平
	pwm1.begin(72000, 500);
	encoder1.begin(1); //1分频
	encoder1.set_polarity_rising(); 
	pwm2.set_oc_polarity(0);//比较匹配后输出低电平
	pwm2.begin(72000, 500);
	encoder2.begin(1); //1分频
	encoder2.set_polarity_rising();
}
int main(void)
{
	setup();
	uart1.begin(115200);
	while (1)
	{   
		led.toggle();
		delay_ms(500);
		uart1.printf("%f %f\r", encoder1.get_wave_peroid(),encoder2.get_wave_frq());
	}
}
#include <stc15.h>
#include <intrins.h>
#include <delay.h>
#include <adc.h>
#include <1602.h>
bit Charging = 0;
sbit LEDSystem = P4^5;
sbit LEDLoad = P2^7;
sbit LEDCharging = P3^7;
sbit EN_Sample = P3^6;
sbit JDQ = P3^5;
void InitIOPort()
{
	P0M0 = 0x00;P0M1 = 0x00;
	P1M0 = 0x00;P1M1 = 0x00;
	P2M0 = 0x00;P2M1 = 0x00;
	P3M0 = 0x60;P3M1 = 0x00;
	P4M0 = 0x00;P4M1 = 0x00;
	P5M0 = 0x00;P5M1 = 0x00;
}
void WatchDogTimer_Config()
{
	WDT_CONTR = 0x3F;
}
void WatchDogTimer_Feed()
{
	WDT_CONTR |= 0x10;
}
int main()
{
	unsigned long ADC0, ADC1, ADC2, ADC3;
	unsigned char time = 0;
	unsigned char t[1] = {'0'};
	InitIOPort();	
	InitADC();
	LCD1602_Init();
	LCD1602_Show(0, 0, "NOT Charging", 12);
	LCD1602_Show(9, 1,"I:" ,2);
	LCD1602_Show(0, 1,"U:" ,2);
	WatchDogTimer_Config();
	LEDSystem = 0;
	LEDLoad = 0;
	while(1)
	{		
		WatchDogTimer_Feed();
		EN_Sample = 0;
		Delay1ms();
		ADC2 = GetADCResult(2);
		ADC3 = GetADCResult(3);
		if(Charging && ADC2 > ADC3)
		{
			LEDCharging = 1;
			LCD1602_Show(0, 0, "NOT Charging", 12);
			Charging = 0;
		}
		else if(!Charging && ADC2 < ADC3)
		{
			LEDCharging = 0;
			LCD1602_AreaClear(0, 0, 16);
			Charging = 1;
			LCD1602_Show(0, 0, "Charging", 8);
		}
		ADC0 = GetADCResult(0);
		ADC1 = GetADCResult(1);		
		EN_Sample = 1;
		ADC0 = ADC0 * 5000 / 1023 * 70 / 51;
		ADC1 = ADC1 * 1500 / 1023;
		
		LCD1602_ShowNum(11, 1, ADC0, 4, 2);
		LCD1602_ShowNum(2, 1, ADC1, 4, 2);
		
		if(ADC0 >= 2300 && JDQ == 1)
		{
			time++;
			if(time >= 5)
			{
				time = 0;
				JDQ = 0;
				LEDLoad = 1;
			}
		}
		else if(ADC0 < 2000 && JDQ == 0)
		{
			JDQ = 1;
			LEDLoad = 0;
			EN_Sample = 0;
			Delay10ms();
			ADC0 = GetADCResult(0);
			EN_Sample = 1;
			ADC0 = ADC0 * 5000 / 1023 * 70 / 51;
			
			if(ADC0 > 2300)
			{
				JDQ = 0;
				LEDLoad = 1;
			}
			LCD1602_ShowNum(11, 1, ADC0, 4, 2);
		}
		else time = 0;
		Delay1000ms();
	}
}
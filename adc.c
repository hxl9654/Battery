#include<stc15.h>
#include<intrins.h>

#define ADC_POWER   0x80            //ADC电源控制位
#define ADC_FLAG    0x10            //ADC完成标志
#define ADC_START   0x08            //ADC起始控制位
#define ADC_SPEEDLL 0x00            //540个时钟
#define ADC_SPEEDL  0x20            //360个时钟
#define ADC_SPEEDH  0x40            //180个时钟
#define ADC_SPEEDHH 0x60            //90个时钟

void InitADC();
void Delay(unsigned char n);

/*----------------------------
读取ADC结果
----------------------------*/
unsigned int GetADCResult(unsigned char ch)
{
	unsigned int temp;
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //等待4个NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//等待ADC转换完成
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

	temp = ADC_RES;
	temp = (temp << 2) | ADC_RESL;
    return temp;                 //返回ADC结果
}

/*----------------------------
初始化ADC
----------------------------*/
void InitADC()
{
    P1ASF = 0xff;                   //设置P1口为AD口
    ADC_RES = 0;                    //清除结果寄存器
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay(2);                       //ADC上电并延时
}

/*----------------------------
软件延时
----------------------------*/
void Delay(unsigned char n)
{
    unsigned char x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}


#include<stc15.h>
#include<intrins.h>

#define ADC_POWER   0x80            //ADC��Դ����λ
#define ADC_FLAG    0x10            //ADC��ɱ�־
#define ADC_START   0x08            //ADC��ʼ����λ
#define ADC_SPEEDLL 0x00            //540��ʱ��
#define ADC_SPEEDL  0x20            //360��ʱ��
#define ADC_SPEEDH  0x40            //180��ʱ��
#define ADC_SPEEDHH 0x60            //90��ʱ��

void InitADC();
void Delay(unsigned char n);

/*----------------------------
��ȡADC���
----------------------------*/
unsigned int GetADCResult(unsigned char ch)
{
	unsigned int temp;
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //�ȴ�4��NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//�ȴ�ADCת�����
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

	temp = ADC_RES;
	temp = (temp << 2) | ADC_RESL;
    return temp;                 //����ADC���
}

/*----------------------------
��ʼ��ADC
----------------------------*/
void InitADC()
{
    P1ASF = 0xff;                   //����P1��ΪAD��
    ADC_RES = 0;                    //�������Ĵ���
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay(2);                       //ADC�ϵ粢��ʱ
}

/*----------------------------
�����ʱ
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


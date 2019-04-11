#include "LCD1602.h"
#include "systick.h"

/*
  LCD 1602����ʾ�Ļ���ַΪ0x80,
  ��һ����ʼ��ַΪ0x80+i             iΪ0x00����0x0F
  ��һ����ʼ��ַΪ0x80+0x40+i         iΪ0x00����0x0F
*/

GPIO_InitTypeDef   GPIO_InitStructure;

void LCD_RCC_Config(void)
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
}


void LCD_GPIO_Config(void)
{
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;										 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}


void  Busy_Wait(void)
{
	//��ȡæµ��־,�ȸ�Ϊ����
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	Reset_RS();                                            //ѡ������
	Set_RW();                                              //ѡ���
	Reset_E();                
	delay_ms(1);
	Set_E();
	delay_ms(5);
		 
    while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)==1);    //���æµ��־ 
	
    Reset_E();
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
}

void LCD_Write_Cmd(uint8_t Cmd)
{
	Busy_Wait();
	Reset_RS();
	Reset_RW();
	Reset_E();
	delay_ms(1);
	Set_E();
	GPIO_Write(GPIOD,(0xff00&(Cmd<<8)));
	delay_ms(5);
	Reset_E();
}

void LCD_Write_Data(uint8_t Data)
{
	Busy_Wait();
	Set_RS();
	Reset_RW();
	Reset_E();
	delay_ms(1);
	Set_E();
	GPIO_Write(GPIOD,(0xff00&(Data<<8)));
	delay_ms(5);
	Reset_E();
}


void LCD_Write_String(uint8_t cmd,uint8_t* p)
{ 
	LCD_Write_Cmd(cmd);
	while(*p!='\0')								 
	{
	    LCD_Write_Data(*p++);

	}

}

void LCD1602_Init(void)
{
   LCD_Write_Cmd(0x38);                      //8�ߣ�������ʾ��5X7����
   LCD_Write_Cmd(0x0c);                     //��ʾ���ܿ����ع�꣬����˸
   LCD_Write_Cmd(0x06);                    //д�����ݺ������ƣ���Ļ���ƶ�
   LCD_Write_Cmd(0x01);                   //����
} 

//addΪ�ַ��ţ�iΪ�к� ����д��ʾ�������ҵ���ģ
void lcd1602_write_pic(uint8_t add,uint8_t *pic_num)
{
	unsigned char i;
	add=add<<3;                           //345λΪ�ַ���ַλ
	for(i=0;i<8;i++)
	{   
	    LCD_Write_Cmd(0x40|add+i);        //�ӵ�һ�п�ʼд��
	    LCD_Write_Data(*pic_num++);
    }
}



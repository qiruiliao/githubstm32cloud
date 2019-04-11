#include "LCD1602.h"
#include "systick.h"

/*
  LCD 1602的显示的基地址为0x80,
  第一行起始地址为0x80+i             i为0x00——0x0F
  第一行起始地址为0x80+0x40+i         i为0x00——0x0F
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
	//读取忙碌标志,先改为输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	Reset_RS();                                            //选择命令
	Set_RW();                                              //选择读
	Reset_E();                
	delay_ms(1);
	Set_E();
	delay_ms(5);
		 
    while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)==1);    //检查忙碌标志 
	
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
   LCD_Write_Cmd(0x38);                      //8线，两行显示，5X7点阵
   LCD_Write_Cmd(0x0c);                     //显示功能开，关光标，不闪烁
   LCD_Write_Cmd(0x06);                    //写入数据后光标右移，屏幕不移动
   LCD_Write_Cmd(0x01);                   //清屏
} 

//add为字符号，i为行号 用来写表示上下左右的字模
void lcd1602_write_pic(uint8_t add,uint8_t *pic_num)
{
	unsigned char i;
	add=add<<3;                           //345位为字符地址位
	for(i=0;i<8;i++)
	{   
	    LCD_Write_Cmd(0x40|add+i);        //从第一行开始写起
	    LCD_Write_Data(*pic_num++);
    }
}



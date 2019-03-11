
#include <stdio.h>
#include "pc_usart1.h"
#include "gprs_uart2.h"
#include "gprs_at.h"
#include "data_unit.h"
#include "gpio.h"
#include "systick.h"
#include "tim.h"

int main()
{
	systick_init();                    // 系统滴答时钟初始化，用于延时处理
    tim3_init();                       // 定时器2初始化
	usart1_init(9600);                // 串口1初始化，用于 PC 端与 MCU 通信
	usart2_init(9600);                // 串口2初始化，用于 GPRS 与 MCU 通信
	gpio_config();                   // GPIO 配置 LED 灯，核心板 PEN 引脚
	PEN_ON;                          // 使能核心板
	printf("SIM800S模块发短信和打电话测试\r\n");	
	while(1)
	{
		if(!gprs_init_flag)                 // 如果核心板未初始化
		{ 
		  err_num = gprs_init();            // 核心板初始化，并将初始化结果保存在 err_num
		}	
		delay_ms(1000);                     //加个延时，不然串口助手显示太快，缓缓
		if(gprs_init_flag)                     // 如果核心板初始化完成
       {
            err_num = gprs_getbor_inf();         // 得到核心板的信息
         } 
		delay_ms(3000);   
		if(gprs_init_flag && (!err_num))       // 没有出错就数据数据处理
		{   delay_ms(3000);
			err_num=gprs_phone();
			 
			
		}
		if(!err_num)
		  {  delay_ms(5000);
		     err_num=gprs_send_message();
		   }
		if((!gprs_init_flag) && err_num)  // 配置未通过
		{
			printf("%d",err_num);
		    err_process(err_num);                // AT命令错误处理
		}		
	
	}

}


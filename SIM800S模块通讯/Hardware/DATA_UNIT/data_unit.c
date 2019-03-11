/********************************************************************************
* @file    			data_unit.c
* @function     数据处理单元  				  				
* @brief 				用3.5.0版本库建的工程模板             
* @attention		该例程仅作为参考，如需实际开发，请根据实际需求更改	
* @version 			V1.0		
* @company  		深圳市飞思创电子科技有限公司
* @website  		https://freestrong.taobao.com
* @Author       WisBarry
* @date    			2018-11-10	
********************************************************************************/

#include "data_unit.h"
#include "pc_usart1.h"
#include "gprs_uart2.h"
#include "gpio.h"
#include "systick.h"
#include "gprs_at.h"
#include "string.h"
#include "tim.h"

uint8_t err_cnt = 0,err_num = 0;   // ERROR 计数，错误值
  
/**
  * @brief  错误处理函数
  * @param  错误值
  * @retval 无
  * @note   出错处理函数，当错误次数超过三次，则重启核心板。
  */
void err_process(uint8_t err)
{
	printf("开始进行错误处理\r\n");
	switch(err)
	{
		case 1:
			printf("AT ERROR\r\n");
		    err_cnt = 4;                     // 如果发送AT命令，核心板没有反应，则直接重启。cnt值为4为重启
		break;
		case 2:
			printf("查询信号强度失败\r\n");
		break;
		case 3:
			printf("读卡失败，请检查SIM卡是否已插入\r\n");
		break;
		case 4:
		  printf("网络注册失败\r\n");
		break;
		case 5:
		     { printf("网络附着失败,重启射频\r\n");
		       printf("AT+CFUN=1,1\r\n");
		     }
		break;
		case 6:
			printf("打电话失败\r\n");
		break;
		case 7:
			printf("查询模块核心板全部基本信息失败\r\n");	
		break;
		case 8:
		  printf("选择短信模式失败\r\n");
		break;
		case 9:
			printf("填写短信号码失败\r\n");
		break;
		case 10:
			printf("写短信内容失败\r\n");
		break;
		case 11:
			printf("短息结束标志填写失败\r\n");
		break;
		case 12:
			printf("获取运营商失败");
		break;
		default:
			printf("初始化完成\r\n");
	}
    gprs_init_flag = 0;	               // 标志位置0
	err_cnt++;
	if(err_cnt >=	3)                   // 出错大于等于三次
	{
		err_cnt = 0;
		gprs_reset();	                   // 重启核心板
	}
}

//重启函数，关机三秒后重启
void gprs_reset(void)
{
	printf("重启模块\r\n");
	PEN_OFF;
	delay_ms(3000);
	PEN_ON;
}

/**
  * @brief  判断缓存中是否含有指定的字符串
  * @param  p 指定的字符串
  * @retval 无
  * @note   1 -- 存在指定的字符串
  *         0 -- 未找到指定的字符串
  */
uint8_t find_string(char* p)
{ 
	if(strstr(gprs_buf,p)!=NULL)
	{
		return 1;
	}
	else
	{
	    return 0;
	}
}

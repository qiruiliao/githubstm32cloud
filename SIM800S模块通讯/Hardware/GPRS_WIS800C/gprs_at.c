#include "gprs_at.h"
#include "gprs_uart2.h"
#include "pc_usart1.h"
#include "systick.h"

uint8_t gprs_init_flag = 0;                                                 //GPRS初始化完成标志，
uint8_t gprs_net_flag = 0;                                                 //网络配置完成标志
uint8_t gprs_connect_flag = 0;       									 //连接成功标志


 //GPRS 初始化配置   delay_ms()延时为防止串口接收信息太快，下一条命令又发出
uint8_t gprs_init(void)
{
	printf("AT\r\n");                                                 // 测试AT命令通信是否正常
	if(gprs_send_cmd("AT\r\n","OK",400,2))                           //等待返回时间500ms，发5次。若接收到OK则返回1
	{
		return 1;	
	}
	delay_ms(1000);
	printf("AT+CSQ\r\n");                                         // 查询信号强弱
	if(gprs_send_cmd("AT+CSQ\r\n","+CSQ:",200,1))
	{
		return 2;	
	}
	delay_ms(1000);
	printf("AT+CPIN?\r\n");                                     // 查询核心板是否读到卡
	if(gprs_send_cmd("AT+CPIN?\r\n","+CPIN: READY",200,1))
	{
		return 3;	
	}
	delay_ms(1000);
	printf("\r\nAT+CREG?\r\n");                              // 查询网络注册情况，核心板会自动注册网络，上电到注册大概 10s 左右
	if(gprs_send_cmd("AT+CREG?\r\n","+CREG:",200,1))
	{
		return 4;	
	}
	delay_ms(1000);
	printf("AT+CGATT?\r\n");                                // 查询核心板是否附着网络
	if(gprs_send_cmd("AT+CGATT?\r\n","+CGATT: 1",500,2))  
	{
		return 5;	
	}
	delay_ms(1000);
	printf("AT+COPS?\r\n");
	if(gprs_send_cmd("AT+COPS?\r\n","+COPS",500,2))     // 查询注册网络运营商网络信息
	{
		return 12;	
	}
	delay_ms(3000);
	printf("GPRS 初始化完成\r\n");
	
    gprs_init_flag = 1;                                  // 初始化完成，标志位置1 
    return 0;
}



     //拨打电话
uint8_t gprs_phone()
{    delay_ms(3000);
     printf("\r\nATD15622164415;\r\n");                                           // 查询核心板型号
	if(gprs_send_cmd("ATD15622164415;\r\n","OK",500,1))                       
	{
		return 6;	
	}
	delay_ms(3000);
        return 0;
}

 //查询核心板全部基本信息
uint8_t gprs_getbor_inf()                                               
{
    delay_ms(2000);
    printf("AT+GSV\r\n");                                                   // 查询核心板全部基本信息
	if(gprs_send_cmd("AT+GSV\r\n","AirM2M",500,1))                       
	{
		return 7;	
	}
	delay_ms(8000);
	return 0;
}

    //发送信息
uint8_t gprs_send_message()
{
	 printf("\r\nAT+CSCSF=\"GSM\"\r\n");
     if(gprs_send_cmd("AT+CSCSF=\"GSM\"\r\n","OK",500,1))                  //发送信息模式
	  {
		return 13;	
	  }
     delay_ms(5000);
	 printf("AT+CMGF=1\r\n");
     if(gprs_send_cmd("AT+CMGF=1\r\n","OK",500,1))                      //选择文本模式
	 {
		return 8;	
	 }
	 delay_ms(5000); 
	 printf("AT+CMGS=\"15622164415\"r\n");
	 if(gprs_send_cmd("AT+CMGS=\"15622164415\"r\n",">",500,1))    // 给15622164415号码发送信息
	 {
		return 9;	
	 }
	 delay_ms(5000);
	 printf("message test");
	 if(gprs_send_cmd("message test",">",500,1))              //发送信息的内容
	 {
		return 10;	
	 }
	 delay_ms(5000);
	 printf("%c",0x1a);
	 if(gprs_send_cmd("0x1a","+CMGS: 11",1000,1))           // 信息的结束符  0x1a
	 {
		return 11;	
	 }
     return 0;
	
}



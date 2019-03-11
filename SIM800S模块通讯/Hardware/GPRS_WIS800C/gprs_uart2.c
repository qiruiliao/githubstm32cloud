#include "gprs_uart2.h"
#include "pc_usart1.h"
#include <string.h>
#include "systick.h"

char gprs_buf[1024];                       // gprs 接收缓存
uint32_t gprs_cnt = 0;                    // gprs接收计数
uint8_t usart2_rev_cnt = 0;               //串口2接收计数，
uint8_t usart2_rev_flag = 0;             //串口2接收标志
uint8_t usart2_rev_finish = 0;          //串口接收完成标志

void usart2_parameter_config(uint32_t baud);    
void usart2_gpio_config(void);
void usart2_nvic_config(void);

//串口2初始化
void usart2_init(uint32_t baud)
{	
	usart2_gpio_config();                                     // 端口2工作模式设置
	usart2_nvic_config();
	usart2_parameter_config(baud);                            // 串口2工作参数设置	
}

 //串口2    gpio口设置
void usart2_gpio_config(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;	
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	    // 使能USART2和GPIOA外设时钟 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
   USART_DeInit(USART2);                                        //  复位串口2
	
   // USART2_TXD(PA.2)  
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			          
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	            // 复用推挽输出
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	        // 设置引脚输出最大速率为50MHz
   GPIO_Init(GPIOA, &GPIO_InitStructure);				        // 调用库函数中的GPIO初始化函数，初始化USART1_TXD(PA.2) 
  
   // USART2_RXD(PA.3)
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				         
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	    // 浮空输入
   GPIO_Init(GPIOA, &GPIO_InitStructure);					    // 调用库函数中的GPIO初始化函数，初始化USART1_RXD(PA.3)
}




 //串口2参数设置8-1-N
void usart2_parameter_config(uint32_t baud)
{
	USART_InitTypeDef   USART_InitStructure;
	/*USART1 初始化设置*/
	USART_InitStructure.USART_BaudRate = baud;	                             			// 设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		        			// 8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;		            			// 1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;			              			// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						// 工作模式设置为收发模式
    USART_Init(USART2, &USART_InitStructure);			                       		    // 初始化串口1
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);       								// 使能串口2接收中断 接收到的非空中断 
	USART_Cmd(USART2, ENABLE);                            								// 使能串口  

}


  //串口2中断向量配置
void usart2_nvic_config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                            // 定义NVIC初始化结构体
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                 // 设置中断优先级组为2，先占优先级和从优先级各两位(可设0～3)
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;               // 串口2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	        // 设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		        // 设置响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			        // IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	
}

/**
  * @brief  串口2发送字符串
  * @param  str：要发送的数据
  *		    len：数据长度
  * @retval 无
  * @note   无
  */
void usart2_send_string(unsigned char *str, unsigned short len)
{
	uint8_t count = 0;
	for(; count < len; count++)
	{
		USART_SendData(USART2, *str++);								                      	// 发送数据
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);		        // 等待发送完成
	}
}

/**
  * @brief  串口2发送命令
  * @param  cmd：命令
  *			res：需要检查的返回指令
  *         timeOut 等待返回时间
  *         resnum 命令发送次数
  * @retval 无
  * @note   0-成功	1-失败
  */
uint8_t gprs_send_cmd(char *cmd,char *res,uint32_t timeOut,uint8_t retime)
{
	uint8_t i = 0;
	uint32_t timeout;
	for(i=0;i<retime;i++)
	{
	    timeout = timeOut;
		//调用串口的发送字符串函数来发送命令
		usart2_send_string((unsigned char *)cmd, strlen((const char *)cmd));
		//在发送命令后的设定时间内串口收到的信息，每次接收后延迟10ms
		//来看看发送接收到第一次数据后在时间内还有没有数据发来
		while(timeout--)
		{
			if(usart2_rev_finish)							                  // 如果串口接收完成
			{
				if(strstr((const char *)gprs_buf, res) != NULL)		         // 如果检索到关键词
				{
					printf("%s",gprs_buf);
					gprs_clear();										     // 清空缓存		
					return 0;
				}
			}	
			delay_ms(25);                                                   //等待下一次接收                                           
		}
		     //在发送一次命令后，规定时间timeout内收到的数据后清空缓存，等待下一次发送命令再接受数据。
		   gprs_clear();                                                      
  }
	return 1;
}

    //GPRS清除数据缓存，调用memset()函数
void gprs_clear(void)
{   //memset函数把0送给数组，即清除数组
	
	memset(gprs_buf, 0, sizeof(gprs_buf));
	gprs_cnt = 0;
}



    //串口2中断处理函数
void usart2_interrupt_process(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)       // 接收中断 接收寄存器非空，即可读数据
	{
		USART_ClearFlag(USART2, USART_FLAG_RXNE);                // 清除标志位
		usart2_rev_flag = 1;                                     // 串口2 接收标志
        usart2_rev_cnt = 0;	                                     // 串口2接收计数清零	
	    gprs_buf[gprs_cnt++] = USART2->DR;                       // 存入缓存数组
		if(gprs_cnt >= sizeof(gprs_buf))
		{
			 gprs_cnt = 0;                                        // 防止数据量过大
		}		
	}
}



#include "pc_usart1.h"
#include <string.h>

void usart1_gpio_config(void);
void usart1_parameter_config(uint32_t baud);
void usart1_nvic_config(void);


// 串口1初始化     
void usart1_init(uint32_t baud)
{
  usart1_gpio_config();                                // 串口1工作模式设置
  usart1_nvic_config();	
  usart1_parameter_config(baud);                       // 串口1工作参数设置		
}

/**
  * @brief  串口1的GPIO端口配置   
  * @param  无
  * @retval 无
  * @note   串口1时钟是挂载在APB2上
  */
void usart1_gpio_config()
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);      // 使能USART1和GPIOA外设时钟 
	USART_DeInit(USART1);		                                                      //复位串口1

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			                             // USART1_TXD(PA.9)     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		                            // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	                           // 设置引脚输出最大速率为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);				           // 调用库函数中的GPIO初始化函数，初始化USART1_RXD(PA.10)

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				                      // USART1_RXD(PA.10)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	                     // 浮空输入

	GPIO_Init(GPIOA, &GPIO_InitStructure);				         // 调用库函数中的GPIO初始化函数，初始化USART1_RXD(PA.10)
}


//串口1参数设置
void usart1_parameter_config(uint32_t baud)
{
	USART_InitTypeDef USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate = baud;	                                            // 设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		                       // 8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;		                          // 1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;			                         // 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	     // 无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;				         // 工作模式设置为收发模式
 
	USART_Init(USART1, &USART_InitStructure);			                                 // 初始化串口1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                                      // 使能串口1接收中断
	USART_Cmd(USART1,ENABLE);    
}

//串口1中断向量初始化
void usart1_nvic_config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                                // 定义NVIC初始化结构体
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                     // 设置中断优先级组为2，先占优先级和从优先级各两位(可设0～3)	

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;				    // 串口1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	        // 设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			        // 设置响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				        // 使能NVIC
	NVIC_Init(&NVIC_InitStructure);	
}

/**
  * @brief  重定向c库函数printf到串口，重定向后可使用printf函数
  * @param  无
  * @retval 无
  * @note   无
  */
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);	                             // 发送一个字节数据到串口
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	     // 等待发送完毕
	return (ch);
}

  

//串口1中断处理，用来清除中断标志
void usart1_interrupt_process(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)               // 接收中断
	{	
		USART_ClearFlag(USART1, USART_FLAG_RXNE);                       // 清空标志位
	} 
}


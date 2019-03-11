#include "pc_usart1.h"
#include <string.h>

void usart1_gpio_config(void);
void usart1_parameter_config(uint32_t baud);
void usart1_nvic_config(void);


// ����1��ʼ��     
void usart1_init(uint32_t baud)
{
  usart1_gpio_config();                                // ����1����ģʽ����
  usart1_nvic_config();	
  usart1_parameter_config(baud);                       // ����1������������		
}

/**
  * @brief  ����1��GPIO�˿�����   
  * @param  ��
  * @retval ��
  * @note   ����1ʱ���ǹ�����APB2��
  */
void usart1_gpio_config()
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);      // ʹ��USART1��GPIOA����ʱ�� 
	USART_DeInit(USART1);		                                                      //��λ����1

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			                             // USART1_TXD(PA.9)     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		                            // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	                           // ������������������Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);				           // ���ÿ⺯���е�GPIO��ʼ����������ʼ��USART1_RXD(PA.10)

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				                      // USART1_RXD(PA.10)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	                     // ��������

	GPIO_Init(GPIOA, &GPIO_InitStructure);				         // ���ÿ⺯���е�GPIO��ʼ����������ʼ��USART1_RXD(PA.10)
}


//����1��������
void usart1_parameter_config(uint32_t baud)
{
	USART_InitTypeDef USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate = baud;	                                            // ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		                       // 8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;		                          // 1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;			                         // ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	     // ��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;				         // ����ģʽ����Ϊ�շ�ģʽ
 
	USART_Init(USART1, &USART_InitStructure);			                                 // ��ʼ������1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                                      // ʹ�ܴ���1�����ж�
	USART_Cmd(USART1,ENABLE);    
}

//����1�ж�������ʼ��
void usart1_nvic_config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                                // ����NVIC��ʼ���ṹ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                     // �����ж����ȼ���Ϊ2����ռ���ȼ��ʹ����ȼ�����λ(����0��3)	

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;				    // ����1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	        // ������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			        // ������Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				        // ʹ��NVIC
	NVIC_Init(&NVIC_InitStructure);	
}

/**
  * @brief  �ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
  * @param  ��
  * @retval ��
  * @note   ��
  */
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);	                             // ����һ���ֽ����ݵ�����
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	     // �ȴ��������
	return (ch);
}

  

//����1�жϴ�����������жϱ�־
void usart1_interrupt_process(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)               // �����ж�
	{	
		USART_ClearFlag(USART1, USART_FLAG_RXNE);                       // ��ձ�־λ
	} 
}


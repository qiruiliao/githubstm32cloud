#include "gprs_uart2.h"
#include "pc_usart1.h"
#include <string.h>
#include "systick.h"

char gprs_buf[1024];                       // gprs ���ջ���
uint32_t gprs_cnt = 0;                    // gprs���ռ���
uint8_t usart2_rev_cnt = 0;               //����2���ռ�����
uint8_t usart2_rev_flag = 0;             //����2���ձ�־
uint8_t usart2_rev_finish = 0;          //���ڽ�����ɱ�־

void usart2_parameter_config(uint32_t baud);    
void usart2_gpio_config(void);
void usart2_nvic_config(void);

//����2��ʼ��
void usart2_init(uint32_t baud)
{	
	usart2_gpio_config();                                     // �˿�2����ģʽ����
	usart2_nvic_config();
	usart2_parameter_config(baud);                            // ����2������������	
}

 //����2    gpio������
void usart2_gpio_config(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;	
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	    // ʹ��USART2��GPIOA����ʱ�� 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
   USART_DeInit(USART2);                                        //  ��λ����2
	
   // USART2_TXD(PA.2)  
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			          
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	            // �����������
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	        // ������������������Ϊ50MHz
   GPIO_Init(GPIOA, &GPIO_InitStructure);				        // ���ÿ⺯���е�GPIO��ʼ����������ʼ��USART1_TXD(PA.2) 
  
   // USART2_RXD(PA.3)
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				         
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	    // ��������
   GPIO_Init(GPIOA, &GPIO_InitStructure);					    // ���ÿ⺯���е�GPIO��ʼ����������ʼ��USART1_RXD(PA.3)
}




 //����2��������8-1-N
void usart2_parameter_config(uint32_t baud)
{
	USART_InitTypeDef   USART_InitStructure;
	/*USART1 ��ʼ������*/
	USART_InitStructure.USART_BaudRate = baud;	                             			// ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		        			// 8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;		            			// 1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;			              			// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						// ����ģʽ����Ϊ�շ�ģʽ
    USART_Init(USART2, &USART_InitStructure);			                       		    // ��ʼ������1
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);       								// ʹ�ܴ���2�����ж� ���յ��ķǿ��ж� 
	USART_Cmd(USART2, ENABLE);                            								// ʹ�ܴ���  

}


  //����2�ж���������
void usart2_nvic_config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                            // ����NVIC��ʼ���ṹ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                 // �����ж����ȼ���Ϊ2����ռ���ȼ��ʹ����ȼ�����λ(����0��3)
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;               // ����2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	        // ������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		        // ������Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			        // IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	
}

/**
  * @brief  ����2�����ַ���
  * @param  str��Ҫ���͵�����
  *		    len�����ݳ���
  * @retval ��
  * @note   ��
  */
void usart2_send_string(unsigned char *str, unsigned short len)
{
	uint8_t count = 0;
	for(; count < len; count++)
	{
		USART_SendData(USART2, *str++);								                      	// ��������
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);		        // �ȴ��������
	}
}

/**
  * @brief  ����2��������
  * @param  cmd������
  *			res����Ҫ���ķ���ָ��
  *         timeOut �ȴ�����ʱ��
  *         resnum ����ʹ���
  * @retval ��
  * @note   0-�ɹ�	1-ʧ��
  */
uint8_t gprs_send_cmd(char *cmd,char *res,uint32_t timeOut,uint8_t retime)
{
	uint8_t i = 0;
	uint32_t timeout;
	for(i=0;i<retime;i++)
	{
	    timeout = timeOut;
		//���ô��ڵķ����ַ�����������������
		usart2_send_string((unsigned char *)cmd, strlen((const char *)cmd));
		//�ڷ����������趨ʱ���ڴ����յ�����Ϣ��ÿ�ν��պ��ӳ�10ms
		//���������ͽ��յ���һ�����ݺ���ʱ���ڻ���û�����ݷ���
		while(timeout--)
		{
			if(usart2_rev_finish)							                  // ������ڽ������
			{
				if(strstr((const char *)gprs_buf, res) != NULL)		         // ����������ؼ���
				{
					printf("%s",gprs_buf);
					gprs_clear();										     // ��ջ���		
					return 0;
				}
			}	
			delay_ms(25);                                                   //�ȴ���һ�ν���                                           
		}
		     //�ڷ���һ������󣬹涨ʱ��timeout���յ������ݺ���ջ��棬�ȴ���һ�η��������ٽ������ݡ�
		   gprs_clear();                                                      
  }
	return 1;
}

    //GPRS������ݻ��棬����memset()����
void gprs_clear(void)
{   //memset������0�͸����飬���������
	
	memset(gprs_buf, 0, sizeof(gprs_buf));
	gprs_cnt = 0;
}



    //����2�жϴ�����
void usart2_interrupt_process(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)       // �����ж� ���ռĴ����ǿգ����ɶ�����
	{
		USART_ClearFlag(USART2, USART_FLAG_RXNE);                // �����־λ
		usart2_rev_flag = 1;                                     // ����2 ���ձ�־
        usart2_rev_cnt = 0;	                                     // ����2���ռ�������	
	    gprs_buf[gprs_cnt++] = USART2->DR;                       // ���뻺������
		if(gprs_cnt >= sizeof(gprs_buf))
		{
			 gprs_cnt = 0;                                        // ��ֹ����������
		}		
	}
}



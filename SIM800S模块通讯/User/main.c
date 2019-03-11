
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
	systick_init();                    // ϵͳ�δ�ʱ�ӳ�ʼ����������ʱ����
    tim3_init();                       // ��ʱ��2��ʼ��
	usart1_init(9600);                // ����1��ʼ�������� PC ���� MCU ͨ��
	usart2_init(9600);                // ����2��ʼ�������� GPRS �� MCU ͨ��
	gpio_config();                   // GPIO ���� LED �ƣ����İ� PEN ����
	PEN_ON;                          // ʹ�ܺ��İ�
	printf("SIM800Sģ�鷢���źʹ�绰����\r\n");	
	while(1)
	{
		if(!gprs_init_flag)                 // ������İ�δ��ʼ��
		{ 
		  err_num = gprs_init();            // ���İ��ʼ����������ʼ����������� err_num
		}	
		delay_ms(1000);                     //�Ӹ���ʱ����Ȼ����������ʾ̫�죬����
		if(gprs_init_flag)                     // ������İ��ʼ�����
       {
            err_num = gprs_getbor_inf();         // �õ����İ����Ϣ
         } 
		delay_ms(3000);   
		if(gprs_init_flag && (!err_num))       // û�г�����������ݴ���
		{   delay_ms(3000);
			err_num=gprs_phone();
			 
			
		}
		if(!err_num)
		  {  delay_ms(5000);
		     err_num=gprs_send_message();
		   }
		if((!gprs_init_flag) && err_num)  // ����δͨ��
		{
			printf("%d",err_num);
		    err_process(err_num);                // AT���������
		}		
	
	}

}


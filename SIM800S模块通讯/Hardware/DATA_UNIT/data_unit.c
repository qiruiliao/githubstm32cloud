/********************************************************************************
* @file    			data_unit.c
* @function     ���ݴ���Ԫ  				  				
* @brief 				��3.5.0�汾�⽨�Ĺ���ģ��             
* @attention		�����̽���Ϊ�ο�������ʵ�ʿ����������ʵ���������	
* @version 			V1.0		
* @company  		�����з�˼�����ӿƼ����޹�˾
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

uint8_t err_cnt = 0,err_num = 0;   // ERROR ����������ֵ
  
/**
  * @brief  ��������
  * @param  ����ֵ
  * @retval ��
  * @note   ��������������������������Σ����������İ塣
  */
void err_process(uint8_t err)
{
	printf("��ʼ���д�����\r\n");
	switch(err)
	{
		case 1:
			printf("AT ERROR\r\n");
		    err_cnt = 4;                     // �������AT������İ�û�з�Ӧ����ֱ��������cntֵΪ4Ϊ����
		break;
		case 2:
			printf("��ѯ�ź�ǿ��ʧ��\r\n");
		break;
		case 3:
			printf("����ʧ�ܣ�����SIM���Ƿ��Ѳ���\r\n");
		break;
		case 4:
		  printf("����ע��ʧ��\r\n");
		break;
		case 5:
		     { printf("���總��ʧ��,������Ƶ\r\n");
		       printf("AT+CFUN=1,1\r\n");
		     }
		break;
		case 6:
			printf("��绰ʧ��\r\n");
		break;
		case 7:
			printf("��ѯģ����İ�ȫ��������Ϣʧ��\r\n");	
		break;
		case 8:
		  printf("ѡ�����ģʽʧ��\r\n");
		break;
		case 9:
			printf("��д���ź���ʧ��\r\n");
		break;
		case 10:
			printf("д��������ʧ��\r\n");
		break;
		case 11:
			printf("��Ϣ������־��дʧ��\r\n");
		break;
		case 12:
			printf("��ȡ��Ӫ��ʧ��");
		break;
		default:
			printf("��ʼ�����\r\n");
	}
    gprs_init_flag = 0;	               // ��־λ��0
	err_cnt++;
	if(err_cnt >=	3)                   // ������ڵ�������
	{
		err_cnt = 0;
		gprs_reset();	                   // �������İ�
	}
}

//�����������ػ����������
void gprs_reset(void)
{
	printf("����ģ��\r\n");
	PEN_OFF;
	delay_ms(3000);
	PEN_ON;
}

/**
  * @brief  �жϻ������Ƿ���ָ�����ַ���
  * @param  p ָ�����ַ���
  * @retval ��
  * @note   1 -- ����ָ�����ַ���
  *         0 -- δ�ҵ�ָ�����ַ���
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

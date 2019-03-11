#include "gprs_at.h"
#include "gprs_uart2.h"
#include "pc_usart1.h"
#include "systick.h"

uint8_t gprs_init_flag = 0;                                                 //GPRS��ʼ����ɱ�־��
uint8_t gprs_net_flag = 0;                                                 //����������ɱ�־
uint8_t gprs_connect_flag = 0;       									 //���ӳɹ���־


 //GPRS ��ʼ������   delay_ms()��ʱΪ��ֹ���ڽ�����Ϣ̫�죬��һ�������ַ���
uint8_t gprs_init(void)
{
	printf("AT\r\n");                                                 // ����AT����ͨ���Ƿ�����
	if(gprs_send_cmd("AT\r\n","OK",400,2))                           //�ȴ�����ʱ��500ms����5�Ρ������յ�OK�򷵻�1
	{
		return 1;	
	}
	delay_ms(1000);
	printf("AT+CSQ\r\n");                                         // ��ѯ�ź�ǿ��
	if(gprs_send_cmd("AT+CSQ\r\n","+CSQ:",200,1))
	{
		return 2;	
	}
	delay_ms(1000);
	printf("AT+CPIN?\r\n");                                     // ��ѯ���İ��Ƿ������
	if(gprs_send_cmd("AT+CPIN?\r\n","+CPIN: READY",200,1))
	{
		return 3;	
	}
	delay_ms(1000);
	printf("\r\nAT+CREG?\r\n");                              // ��ѯ����ע����������İ���Զ�ע�����磬�ϵ絽ע���� 10s ����
	if(gprs_send_cmd("AT+CREG?\r\n","+CREG:",200,1))
	{
		return 4;	
	}
	delay_ms(1000);
	printf("AT+CGATT?\r\n");                                // ��ѯ���İ��Ƿ�������
	if(gprs_send_cmd("AT+CGATT?\r\n","+CGATT: 1",500,2))  
	{
		return 5;	
	}
	delay_ms(1000);
	printf("AT+COPS?\r\n");
	if(gprs_send_cmd("AT+COPS?\r\n","+COPS",500,2))     // ��ѯע��������Ӫ��������Ϣ
	{
		return 12;	
	}
	delay_ms(3000);
	printf("GPRS ��ʼ�����\r\n");
	
    gprs_init_flag = 1;                                  // ��ʼ����ɣ���־λ��1 
    return 0;
}



     //����绰
uint8_t gprs_phone()
{    delay_ms(3000);
     printf("\r\nATD15622164415;\r\n");                                           // ��ѯ���İ��ͺ�
	if(gprs_send_cmd("ATD15622164415;\r\n","OK",500,1))                       
	{
		return 6;	
	}
	delay_ms(3000);
        return 0;
}

 //��ѯ���İ�ȫ��������Ϣ
uint8_t gprs_getbor_inf()                                               
{
    delay_ms(2000);
    printf("AT+GSV\r\n");                                                   // ��ѯ���İ�ȫ��������Ϣ
	if(gprs_send_cmd("AT+GSV\r\n","AirM2M",500,1))                       
	{
		return 7;	
	}
	delay_ms(8000);
	return 0;
}

    //������Ϣ
uint8_t gprs_send_message()
{
	 printf("\r\nAT+CSCSF=\"GSM\"\r\n");
     if(gprs_send_cmd("AT+CSCSF=\"GSM\"\r\n","OK",500,1))                  //������Ϣģʽ
	  {
		return 13;	
	  }
     delay_ms(5000);
	 printf("AT+CMGF=1\r\n");
     if(gprs_send_cmd("AT+CMGF=1\r\n","OK",500,1))                      //ѡ���ı�ģʽ
	 {
		return 8;	
	 }
	 delay_ms(5000); 
	 printf("AT+CMGS=\"15622164415\"r\n");
	 if(gprs_send_cmd("AT+CMGS=\"15622164415\"r\n",">",500,1))    // ��15622164415���뷢����Ϣ
	 {
		return 9;	
	 }
	 delay_ms(5000);
	 printf("message test");
	 if(gprs_send_cmd("message test",">",500,1))              //������Ϣ������
	 {
		return 10;	
	 }
	 delay_ms(5000);
	 printf("%c",0x1a);
	 if(gprs_send_cmd("0x1a","+CMGS: 11",1000,1))           // ��Ϣ�Ľ�����  0x1a
	 {
		return 11;	
	 }
     return 0;
	
}



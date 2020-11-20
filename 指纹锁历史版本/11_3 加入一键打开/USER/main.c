#include "delay.h"
#include "led.h"

#include "oled.h"
#include "bmp.h"

#include "pwm.h"

#include "public.h"
u8  eu8_Flag = 0;								/*ȫ�ֱ�������һ�����жϱ�־λ*/
u8  eu8_what = 0;        			  /*ȫ�ֱ�������һ���յ���һλ����*/
int DJ1=0;//���������
int FenMin=1; //�������Ƿ���
extern int Shua_ZW_OK;//ȫ�ֱ��� ָ����֤ͨ��Ϊ1
#define usart2_baund  57600			/*����2�����ʣ�����ָ��ģ�鲨���ʸ���*/
SysPara AS608Para;							/*ָ��ģ��AS608����*/
u16 ValidN;											/*ģ������Чָ�Ƹ���*/

int main()
{
	u8 ensure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();								/*��ʱ��ʼ��*/
	USART_INIT();								/*����һ��ʼ��*/
	
	
	
	LED_Init();//LED����������ʼ��

	//AS608_SW=1;
	BEEP=0;
	AS608_SW=1;	
	LED1=1;	

	
//	AS608_SW=0;	
//	delay_ms(1000);
//	LED1=0;
//	
//	AS608_SW=1;	
//	delay_ms(1000);
//	AS608_SW=0;	
	
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	OLED_Refresh();
		
	OLED_ShowString(72,52,"by NF404",12);
	OLED_Refresh();
	
	TIM3_PWM_Init(199,7199);//��ʼ��    4Ϊ0�� 23Ϊ180
  TIM_SetCompare2(TIM3, 4);//TIM3_CH2 ���180�� 

	
	printf("��ʼ����\r\n");
	usart2_init(usart2_baund);	/*��ʼ������2,������ָ��ģ��ͨѶ*/
	PS_StaGPIO_Init();					/*��ʼ��FR��״̬����*/
	printf("��ָ��ģ������\r\n");
	while(PS_HandShake(&AS608Addr))			/*��AS608ģ������*/
	{
		delay_ms(400);
		printf("δ��⵽ģ��\r\n");
		OLED_ShowString(48,20,"NO AS608",12);
		OLED_Refresh();
		
		delay_ms(800);
		printf("������������ģ��\r\n"); 
	}
	printf("ͨѶ�ɹ�\r\n");
	printf("������:%d   ��ַ:%x\r\n",usart2_baund,AS608Addr);		/*��ӡ��Ϣ*/
	ensure=PS_ValidTempleteNum(&ValidN);										/*����ָ�Ƹ���*/
	if(ensure!=0x00)
		ShowErrMessage(ensure);								/*��ʾȷ���������Ϣ*/
	ensure=PS_ReadSysPara(&AS608Para);  		/*������ */
	if(ensure==0x00)
	{
		printf("������:%d     �Աȵȼ�: %d",AS608Para.PS_max-ValidN,AS608Para.PS_level);
	}
	else
		ShowErrMessage(ensure);	
	
	OLED_Clear();
	OLED_ShowChinese(32,32,0,16);//��
	OLED_ShowChinese(48,32,1,16);//��
	OLED_ShowChinese(64,32,2,16);//��
	OLED_ShowChinese(80,32,3,16);//ָ
	//OLED_Refresh();
	OLED_ShowChinese(48,0,0,32);//��
	OLED_ShowString(0,52,"(-_-)  V1.1-by NF404",12);
	//OLED_ShowString(72,52,"V1.1by NF404",12);
	OLED_Refresh();

	
  while(1)
	{
			
			//AS608_SW=0;	
			//usart1_execute();			 /*����һ���յ����������ݺ�ִ���Ӻ���*/
			//OLED_ShowString(32,32,"NI DE YAN JIN",12);
			//OLED_Refresh();
//			OLED_ShowChinese(32,32,0,16);//��
//			OLED_ShowChinese(48,32,1,16);//��
//			OLED_ShowChinese(64,32,2,16);//��
//			OLED_ShowChinese(80,32,3,16);//ָ
//			OLED_Refresh();
			AS608_SW=0;	
			
		if(KEY==1)//��ⰴ��
			{
				delay_ms(10);
				if(KEY==1)
				{
					Shua_ZW_OK=1;
					FenMin=0;
				}
							
			}
			
			if(PS_Sta && Shua_ZW_OK==0)	 //���PS_Sta״̬���������ָ����
			{
			LED1=0;
			AS608_SW=1;
			
			OLED_ShowChinese(32,32,14,16);//����ָ��
			OLED_ShowChinese(48,32,15,16);//
			OLED_ShowChinese(64,32,10,16);//
			OLED_ShowChinese(80,32,11,16);//
			OLED_Refresh();
			
			delay_ms(100);
				
			press_FR();//ˢָ��	
			LED1=1;
			delay_ms(50);
			//AS608_SW=0;
			}
			
			if(Shua_ZW_OK)
			{
				//TIM_SetCompare2(TIM3, 23);
				Shua_ZW_OK=0;//ָ����֤ͨ����־���
				//OLED_Clear();
				OLED_ShowChinese(48,0,1,32);//��1
				OLED_ShowChinese(80,0,2,32);//��2
				OLED_ShowChinese(32,32,4,16);//��
				OLED_ShowChinese(48,32,5,16);//֤
				OLED_ShowChinese(64,32,6,16);//ͨ
				OLED_ShowChinese(80,32,7,16);//��
				OLED_ShowString(0,52,"(>_<)  V1.1-by NF404",12);
				OLED_Refresh();
								
				//TIM_SetCompare2(TIM3, 23);
			
				for(DJ1=4;DJ1<10;DJ1++)
				{
					TIM_SetCompare2(TIM3, DJ1);
					delay_ms(50);
				}
				delay_ms(300);
				if(FenMin)
					{						
						BEEP=0;
						OLED_ShowString(0,0,"Bee~ ~",12);
						OLED_Refresh();
						delay_ms(250);
						BEEP=1;
					}else
						{
							
							FenMin=1;
						}
			
				delay_ms(250);		
				delay_ms(1000);
				delay_ms(1000);
								
				TIM_SetCompare2(TIM3, 4);
				delay_ms(500);
				
				OLED_Clear();
				OLED_ShowString(0,52,"(-_-)  V1.1-by NF404",12);
				OLED_ShowChinese(48,0,0,32);//��
				OLED_ShowChinese(32,32,0,16);//��
				OLED_ShowChinese(48,32,1,16);//��
				OLED_ShowChinese(64,32,2,16);//��
				OLED_ShowChinese(80,32,3,16);//ָ
				OLED_Refresh();			
				AS608_SW=0;
				
				//TIM_SetCompare2(TIM3, 4);
				//OLED_ShowString(32,0,"tongguo",12);
				//OLED_Refresh();
			}else
				{
					OLED_ShowChinese(32,32,0,16);//��
					OLED_ShowChinese(48,32,1,16);//��
					OLED_ShowChinese(64,32,2,16);//��
					OLED_ShowChinese(80,32,3,16);//ָ
					OLED_Refresh();
				}
				
			//a=KEY_Scan();
		//	OLED_ShowNum(0,32,a,3,16);
		//	printf("%d\r\n",a);
	
			
	}
}


#include "pwm.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//PWM  ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM4_PWM_Init(u16 arr,u16 psc)

{ 

      GPIO_InitTypeDef GPIO_InitStructure;
      TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
      TIM_OCInitTypeDef TIM_OCInitStructure;
    
      //ʹ�ܶ�ʱ��TIM4
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
      //ʹ��PWM���GPIOʱ��
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); 
                                                                        
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//��ʱ��TIM4��ͨ��1��TIM4_CH1��PB6��
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//����
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//��ʱ��TIM4��ͨ��1��TIM4_CH2��PB7��
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//����
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//��ʱ��TIM4��ͨ��1��TIM4_CH3��PB8��
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//����
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//��ʱ��TIM4��ͨ��1��TIM4_CH4��PB9��
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//����
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��

      
      TIM_TimeBaseStructure.TIM_Period = arr;//�Զ���װ��ֵ
      TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʱ��Ԥ��Ƶ��
      TIM_TimeBaseStructure.TIM_ClockDivision = 0;
      TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���ģʽ
      TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //��ʼ��TIM4

 
      //��ʼ��TIM_CH1��PWMģʽ

      TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//����pwmģʽ1

      TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��

      TIM_OCInitStructure.TIM_Pulse = 0;

      TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//������Ը�

      TIM_OC1Init(TIM4, &TIM_OCInitStructure);//��ʼ��TIM4_CH1

      

      //��ʼ��TIM_CH2��PWMģʽ

      TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
      TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
      TIM_OCInitStructure.TIM_Pulse = 0;
      TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
      
      TIM_OC2Init(TIM4, &TIM_OCInitStructure);

      
     
			//��ʼ��TIM_CH3��PWMģʽ
      TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
      TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
      TIM_OCInitStructure.TIM_Pulse = 0;
      TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
      
			TIM_OC3Init(TIM4, &TIM_OCInitStructure);

      
      //��ʼ��TIM_CH3��PWMģʽ
      TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
      TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
      TIM_OCInitStructure.TIM_Pulse = 0;
      TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

      TIM_OC4Init(TIM4, &TIM_OCInitStructure);

 

      //ʹ��4��ͨ����Ԥװ�ؼĴ���
      TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);//OC1
      TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);//OC2
      TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);//OC3
      TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);//OC4
     
      TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ����װ��ֵ
      

      TIM_Cmd(TIM4, ENABLE);//ʹ�ܶ�ʱ��TIM4��׼������

}


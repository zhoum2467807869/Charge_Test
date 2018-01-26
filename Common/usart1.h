#ifndef __USART1_H
#define __USART1_H
/**
  ******************************************************************************
  * @file    STM32F407DEMO/usart1.c 
  * @author  Liang
  * @version V1.0.0
  * @date    2017-4-26
  * @brief   
  ******************************************************************************
  * @attention
	* 加入是否支持UCOS宏定义
	* 支持适应不同频率下的串口波特率设置.
	*	加入了对printf的支持
	* 增加了串口接收命令功能.
	* 修正了printf第一个字符丢失的bug
	* 修改串口初始化IO的bug
	* 修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
	* 增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
	* 修改了EN_USART1_RX的使能方式
	* 增加了对UCOSII的支持
  ******************************************************************************
**/

/* include-------------------------------------------------- */
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

/* define--------------------------------------------------- */
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 				1		//使能（1）/禁止（0）串口1接收
	  	
extern u8 USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u8 HMI_RX_FLAG;         		//接收状态标记
extern u8 UASRT1_RX_BUFFER_LEN;  //有效字符长度
extern u8 USART1_0XFF_FLAG;	//oxff计数

void uart1_init(u32 bound);
void HMI_Send_TXEND(void);

#endif



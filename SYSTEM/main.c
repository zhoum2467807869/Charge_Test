/**
  ******************************************************************************
  * @file    STM32F407DEMO/main.c 
  * @author  Liang
  * @version V1.0.0
  * @date    2017-4-26
  * @brief   Main program body
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "sys.h"
#include "led.h"
#include "delay.h"
#include "usart1.h"
#include "sdio_sdcard.h"
#include "mcp3421.h"
#include "myiic.h"
#include "dac.h"
#include "ff.h"  
#include "exfuns.h"
#include "usbd_msc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_conf.h"
#include "usart2.h"
#include <rtthread.h>
#include "CSV_Database.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USB_OTG_CORE_HANDLE USB_OTG_dev;
extern vu8 USB_STATUS_REG;		//USB状态
extern vu8 bDeviceState;		//USB连接 情况

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


static struct rt_thread led0_thread;//线程控制块
static struct rt_thread led1_thread;//线程控制块
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t rt_led0_thread_stack[256];//线程栈
static rt_uint8_t rt_led1_thread_stack[256];//线程栈


//线程LED0
static void led0_thread_entry(void* parameter)
{
	while(1)
	{
		LED0=~LED0;
		delay_ms(300);	
		delay_us(100000);
		rt_thread_delay(100);
	}
}
  
//线程LED1
static void led1_thread_entry(void* parameter)
{
		u32 total,free;
		FIL fsrc;	  		//文件1
		u8 res;
		char str[20];
	
		TestData_Type Temp_struct;
	
		Temp_struct.Test_Time[0]=18;
		Temp_struct.Test_Time[1]=1;
		Temp_struct.Test_Time[2]=22;
		Temp_struct.Test_Time[3]=13;
		Temp_struct.Test_Time[4]=55;
		Temp_struct.Test_Time[5]=18;
		Temp_struct.Ripple_Voltage=200;
		Temp_struct.Vout_Max=200;
		Temp_struct.Cout_Max=150;
		Temp_struct.Over_Current_Protection=1;
		Temp_struct.Over_Voltage_Protection=1;
		Temp_struct.Poweron_Time=20;
		Temp_struct.Quick_Charge=3;
		Temp_struct.Short_Current=1;
		Temp_struct.Efficiency=67;
		Temp_struct.Test_Subsequence=9;
		
		printf("OK");
		exfuns_init();
		if(f_mount(fs[0],"0:",1)) printf("挂载失败");
		printf("挂载成功\r\n");
		if(exf_getfree("0:",&total,&free)) printf("获取错误");
		printf("total=%dMB\r\nfree=%dMB\r\n",total>>10,free>>10);
		//res=Test_WriteData(Temp_struct,"123");
		res=Creat_FileHeader("0:/323.csv");
		printf("rse=%d",res);
	while(1)
	{
//		LED1=~LED1; 
//		delay_ms(10);
//		delay_us(50);
//		rt_thread_delay(30);
	}
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main()
{
//		
//    // 创建静态线程
//    rt_thread_init(&led0_thread,               	  //线程控制块
//                   "led0",                     	  //线程名字，在shell里面可以看到
//                   led0_thread_entry,          	  //线程入口函数
//                   RT_NULL,                    	  //线程入口函数参数
//                   &rt_led0_thread_stack[0],      //线程栈起始地址
//                   sizeof(rt_led0_thread_stack),  //线程栈大小
//                   3,                          	  //线程的优先级
//                   20);                           //线程时间片
//                               
//    rt_thread_startup(&led0_thread);           	  //启动线程led0_thread，开启调度
//				   
    // 创建静态线程                          
	rt_thread_init(&led1_thread,                  //线程控制块
				   "led1",                        //线程名字，在shell里面可以看到
				   led1_thread_entry,             //线程入口函数
				   RT_NULL,                       //线程入口函数参数
				   &rt_led1_thread_stack[0],      //线程栈起始地址
				   sizeof(rt_led1_thread_stack),  //线程栈大小
				   3,                             //线程的优先级
				   20);                           //线程时间片     

	rt_thread_startup(&led1_thread);              //启动线程led1_thread，开启调度  	
		
		return 0;
}




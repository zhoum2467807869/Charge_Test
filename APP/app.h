#ifndef _APP_H
#define _APP_H
/**
  ******************************************************************************
  * @file    STM32F407DEMO/app.h 
  * @author  Liang
  * @version V1.0.0
  * @date    2018-1-22
  * @brief   
  ******************************************************************************
  * @attention
	* 加入对rt-thread的支持
	*	用于rt-thread msh的串口驱动
  ******************************************************************************
**/

#include <rtthread.h>

/* 邮箱控制块 */
static struct rt_mailbox HMI_Response_mb;		//HMI串口响应邮箱
static rt_mailbox_t GetData_mb=RT_NULL;					//数据采集邮箱
static rt_mailbox_t Event_mb=RT_NULL;						//按键动作邮箱

/* 用于放邮件的内存池 */
static char mb_pool[32];
static rt_uint8_t Event_Flag;

static rt_uint8_t Batch_val;	//批量序号
static rt_uint8_t Standard_val; //测试标准序号

static rt_thread_t led0_thread=RT_NULL;
static rt_thread_t led1_thread=RT_NULL;
static rt_thread_t usb_thread=RT_NULL;
static rt_thread_t HMIMonitor_thread=RT_NULL;
static rt_thread_t Master_thread=RT_NULL;
static rt_thread_t CollectData_thread=RT_NULL;
static rt_thread_t HMI_FastTest_thread=RT_NULL;
static rt_thread_t HMI_ShowBatchList_thread=RT_NULL;
static rt_thread_t HMI_SelectBatch_thread=RT_NULL;

void led0_thread_entry(void* parameter);
void usb_thread_entry(void* parameter);
void led1_thread_entry(void* parameter);
void HMIMonitor_thread_entry(void* parameter);
void Master_thread_entry(void* parameter);
void CollectData_thread_entry(void* parameter);
void HMI_FastTest_thread_entry(void* parameter);	//快速检测HMI界面线程
void HMI_ShowBatchList_thread_entry(void* parameter); //批量列表显示界面线程
void HMI_SelectBatch_thread_entry(void* parameter);	//批量选择线程
void cpu_usage_idle_hook(void);
void Main_entry(void);

void cpu_usage_get(rt_uint8_t *major, rt_uint8_t *minor);


#endif


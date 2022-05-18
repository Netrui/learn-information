#ifndef __ds1302_H 
#define __ds1302_H  
 
#include "sys.h" 
#include "stm32f10x.h" 

#define CE_L GPIO_ResetBits(GPIOC,GPIO_Pin_3)        
#define CE_H GPIO_SetBits(GPIOC,GPIO_Pin_3)
#define SCLK_L GPIO_ResetBits(GPIOC,GPIO_Pin_5)     
#define SCLK_H  GPIO_SetBits(GPIOC,GPIO_Pin_5)				
#define DATA_L  GPIO_ResetBits(GPIOC,GPIO_Pin_4)     
#define DATA_H  GPIO_SetBits(GPIOC,GPIO_Pin_4)
 
struct TIMEData
{
	u16 year;
	u8  month;
	u8  day;
	u8  hour;
	u8  minute;
	u8  second;
	u8  week;
};
extern struct TIMEData TimeData;

void ds1302_gpio_init();
void ds1302_write_onebyte(u8 data);
void ds1302_wirte_rig(u8 address,u8 data);
u8 ds1302_read_rig(u8 address);
void ds1032_init();
void ds1032_DATAOUT_init();
void ds1032_DATAINPUT_init();
void ds1032_read_time();
void ds1032_read_realTime();
 
#endif
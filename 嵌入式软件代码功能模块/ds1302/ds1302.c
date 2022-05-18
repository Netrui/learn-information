#include "ds1302.h"
#include "sys.h"
#include "delay.h"
 
struct TIMEData TimeData;
u8 read_time[7];
 
void ds1302_gpio_init()
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(GPIOA, &GPIO_InitStructure);
GPIO_ResetBits(GPIOA,GPIO_Pin_5); 
 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(GPIOA, &GPIO_InitStructure);
GPIO_ResetBits(GPIOA,GPIO_Pin_3); 
}
 
void ds1032_DATAOUT_init()
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(GPIOA, &GPIO_InitStructure);
GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}
 
void ds1032_DATAINPUT_init()
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
GPIO_Init(GPIOA, &GPIO_InitStructure);
}
 
 
void ds1302_write_onebyte(u8 data)
{
	ds1032_DATAOUT_init();
	u8 count=0;
	SCLK_L;
	for(count=0;count<8;count++)
		{	SCLK_L;
			if(data&0x01)
			{DATA_H;}
			else{DATA_L;}
			SCLK_H;
			data>>=1;
		}
}
 
void ds1302_wirte_rig(u8 address,u8 data)
{
u8 temp1=address;
u8 temp2=data;
CE_L;SCLK_L;delay_us(1);
CE_H;delay_us(2);
ds1302_write_onebyte(temp1);
ds1302_write_onebyte(temp2);
CE_L;SCLK_L;delay_us(2);
}
 
u8 ds1302_read_rig(u8 address)
{
		u8 temp3=address;
		u8 count=0;
		u8 return_data=0x00;
		CE_L;
		SCLK_L;
		delay_us(3);
		CE_H;
		delay_us(3);
		ds1302_write_onebyte(temp3);
		ds1032_DATAINPUT_init();
		delay_us(2);
		for(count=0;count<8;count++)
			{
			delay_us(2);
			return_data>>=1;
			SCLK_H;delay_us(4);
			SCLK_L;delay_us(14);
			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10))
			{return_data=return_data|0x80;}
			
			}
		delay_us(2);
		CE_L;
		DATA_L;
		return return_data;
}
 
void ds1032_init()
{
ds1302_wirte_rig(0x8e,0x00);
ds1302_wirte_rig(0x80,0x37);
ds1302_wirte_rig(0x82,0x58);
ds1302_wirte_rig(0x84,0x23);
ds1302_wirte_rig(0x86,0x30);
ds1302_wirte_rig(0x88,0x09);
ds1302_wirte_rig(0x8a,0x07);
ds1302_wirte_rig(0x8c,0x20);
ds1302_wirte_rig(0x8e,0x80);
}
 
void ds1032_read_time()
{
read_time[0]=ds1302_read_rig(0x81);
read_time[1]=ds1302_read_rig(0x83);
read_time[2]=ds1302_read_rig(0x85);
read_time[3]=ds1302_read_rig(0x87);
read_time[4]=ds1302_read_rig(0x89);
read_time[5]=ds1302_read_rig(0x8B);
read_time[6]=ds1302_read_rig(0x8D);
}
 
void ds1032_read_realTime()
{
ds1032_read_time();  
TimeData.second=(read_time[0]>>4)*10+(read_time[0]&0x0f);
TimeData.minute=((read_time[1]>>4)&(0x07))*10+(read_time[1]&0x0f);
TimeData.hour=(read_time[2]>>4)*10+(read_time[2]&0x0f);
TimeData.day=(read_time[3]>>4)*10+(read_time[3]&0x0f);
TimeData.month=(read_time[4]>>4)*10+(read_time[4]&0x0f);
TimeData.week=read_time[5];
TimeData.year=(read_time[6]>>4)*10+(read_time[6]&0x0f)+2000;
}
#ifndef __JOYPAD_H
#define __JOYPAD_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 


//��Ϸ�ֱ����� ����	   


//�޸�����:2012/9/12
//�汾��V1.0


//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//�ֱ���������
#define JOYPAD_CLK PCout(12)  	//ʱ��		PC9
#define JOYPAD_LAT PCout(8)  	//����     	PC8
#define JOYPAD_DAT PCin(9)	 	//����     	PC12    

void JOYPAD_Init(void);			//��ʼ��	
u8 JOYPAD_Read(void);			//��ȡ��ֵ	 				    
#endif

















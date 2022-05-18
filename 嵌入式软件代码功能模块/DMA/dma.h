#ifndef __DMA_H
#define	__DMA_H	   
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 


//DMA 代码	   


//修改日期:2012/9/8
//版本：V1.0


//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
							    					    

void MYDMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);//配置DMA1_CHx
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx);//使能DMA1_CHx		   
#endif































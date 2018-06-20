#include "sys.h"
#include "delay.h"

#include "port.h"
#include "mbport.h"
#include "mb.h"

int main(void)
{
	HAL_Init();                    	 	//初始化HAL库,中断分租默认4    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//设置时钟,72M
	delay_init(72);               		//初始化延时函数
	
    eMBInit(MB_RTU, 0x01, 2, 115200, MB_PAR_NONE);
	eMBEnable(  );
	
    while(1){
      eMBPoll(  );
    }
}




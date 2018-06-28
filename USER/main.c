#include "sys.h"
#include "delay.h"

#include "port.h"
#include "mbport.h"
#include "mb.h"

#include "hci.h"
#include "visEffect.h"

int main(void)
{
	HAL_Init();                    	 	//初始化HAL库,中断分组默认4
    Stm32_Clock_Init(RCC_PLL_MUL8);   	//设置时钟,64M
	delay_init(64);               		//初始化延时函数
    
    hci_init();
	
    eMBInit(MB_RTU, 0x01, 2, 115200, MB_PAR_NONE);
	eMBEnable();
    
    visInit();
	
    while(1){
      /*处理modbus事务，接收并解析modbus命令*/
      eMBPoll();
        
      visHandle();
      /*处理modbus事物*/
        
      /*接收到控制命令发送完毕指令，取出命令，更新缓存*/
    }
}

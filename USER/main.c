#include "sys.h"
#include "delay.h"

#include "port.h"
#include "mbport.h"
#include "mb.h"

#include "hci.h"
#include "visEffect.h"

int main(void)
{
	HAL_Init();                    	 	//��ʼ��HAL��,�жϷ���Ĭ��4
    Stm32_Clock_Init(RCC_PLL_MUL8);   	//����ʱ��,64M
	delay_init(64);               		//��ʼ����ʱ����
    
    hci_init();
	
    eMBInit(MB_RTU, 0x01, 2, 115200, MB_PAR_NONE);
	eMBEnable();
    
    visInit();
	
    while(1){
      /*����modbus���񣬽��ղ�����modbus����*/
      eMBPoll();
        
      visHandle();
      /*����modbus����*/
        
      /*���յ�������������ָ�ȡ��������»���*/
    }
}

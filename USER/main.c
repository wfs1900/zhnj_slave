#include "sys.h"
#include "delay.h"

#include "port.h"
#include "mbport.h"
#include "mb.h"

int main(void)
{
	HAL_Init();                    	 	//��ʼ��HAL��,�жϷ���Ĭ��4    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//����ʱ��,72M
	delay_init(72);               		//��ʼ����ʱ����
	
    eMBInit(MB_RTU, 0x01, 2, 115200, MB_PAR_NONE);
	eMBEnable(  );
	
    while(1){
      /*����modbus���񣬽��ղ�����modbus����*/
      eMBPoll(  );
        
      /*����modbus����*/
        
      /*���յ�������������ָ�ȡ��������»���*/
    }
}

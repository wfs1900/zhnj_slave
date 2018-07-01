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
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//����ʱ��,64M
	delay_init(72);               		//��ʼ����ʱ����
    
    hci_init();
	
    eMBInit(MB_RTU, 0x01, 2, 115200, MB_PAR_NONE);
	eMBEnable();
    
    visInit();
	
    while(1){
      /*����modbus���񣬽��ղ�����modbus����*/
      eMBPoll();
      
      /*delay_ms(500);
      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET);         
      delay_ms(500);
      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET); 
      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET); */
      visHandle();
      /*����modbus����*/
        
      /*���յ�������������ָ�ȡ��������»���*/
    }
}

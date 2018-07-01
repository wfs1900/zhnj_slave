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
      hci_do_led(1,0);  
      eMBPoll();
      
      /*delay_ms(500);
      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET);         
      delay_ms(500);
      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET); 
      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET); */
      visHandle();
      /*����modbus����*/

        hci_do_led(1,1);
        
      /*���յ�������������ָ�ȡ��������»���*/
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
		hci_do_led(1,0);
		HAL_Delay (50);
  }
  /* USER CODE END Error_Handler */ 
}

#include "delay.h"
#include "hci.h"
#include "stm32f1xx.h"

void hci_init(void) {

    GPIO_InitTypeDef GPIO_InitStructure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();           	//开启GPIOA时钟
	__HAL_RCC_GPIOB_CLK_ENABLE();           	//开启GPIOB时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();           	//开启GPIOC时钟
    

    __HAL_AFIO_REMAP_SWJ_NOJTAG();//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    /*pin15:wifi-g*/
    GPIO_InitStructure.Pin   = GPIO_PIN_15;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*pin3:wifi-r, pin4:op1-r, pin5:op1-g,  pin8:op2-r, pin9:op2-g, pin12:buzz*/
    GPIO_InitStructure.Pin   = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9 |  GPIO_PIN_12 ;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Pin   = GPIO_PIN_13;  //工作指示灯
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    hci_do_led(0,0);
    hci_do_led(1,0);
    hci_do_led(2,0);
    hci_do_led(3,0);
    hci_do_led(4,0);
}

void hci_do_led(uint16_t slot_addr, uint8_t sw)
{
    switch(slot_addr){
    
        case 0:
            //wifi led  LED_WIFI_R-GPIO_Pin_15 LED_WIFI_G-GPIO_Pin_3
            if(sw){
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
               HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET); 
            }else{
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
               HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET); 
            }
        break;
        
        case 1:
            //sys led  LED_SYS-GPIO_Pin_13
            if(sw){
               HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
            }else{
               HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
            }
        break;
                
        case 2:
            //gnd led  LED_GND_R-GPIO_Pin_8   LED_GND_G-GPIO_Pin_9
            if(sw){
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET);
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
            }else{
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET);
            }
        break;
        
        case 3:
            //weared led  LED_WEARED_R-GPIO_Pin_4  LED_WEARED_G-GPIO_Pin_5
            if(sw){
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);
            }else{
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);
            }
        break;
        
        case 4:
            //alarm  CTRL_ALARM-GPIO_Pin_12
            if(sw){
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
            }else{
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
            }
        break;
    }
}

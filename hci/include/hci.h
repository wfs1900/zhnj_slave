#ifndef _HCI_H
#define _HCI_H

void hci_init(void);

void hci_do_led(uint16_t slot_addr, uint8_t state);

/*GPIOA*/
#define LED_WIFI_R      GPIO_Pin_15
/*GPIOB*/
#define LED_WIFI_G      GPIO_Pin_3

#define LED_WEARED_R    GPIO_Pin_4
#define LED_WEARED_G    GPIO_Pin_5

#define LED_GND_R       GPIO_Pin_8
#define LED_GND_G       GPIO_Pin_9

/*GPIOB*/
#define CTRL_ALARM      GPIO_Pin_12

/*GPIOC*/
#define LED_SYS         GPIO_Pin_13

#endif

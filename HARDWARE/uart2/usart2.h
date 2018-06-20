#ifndef _USART2_H
#define _USART2_H

#include "port.h"

void usart_config(uint8_t port, uint32_t baud, uint16_t data_bits, uint16_t parity);
void usart_send_byte(void *buf, uint16_t buf_len);
uint8_t usart_get_byte(void);
void usart_rx_it(BOOL sw); //是否开启接收中断
void usart_tx_it(BOOL sw); //是否开启发送中断

void open_485_send(void);
void close_485_send(void);
#endif

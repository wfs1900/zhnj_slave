#include "usart2.h"
#include "stm32f1xx.h"

extern void prvvUARTTxReadyISR( void );  //串口发送中断中调用
extern void prvvUARTRxISR( void );       //串口接收中断中调用

UART_HandleTypeDef USART2_RS485Handler;

void open_485_send()
{
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);
}

void close_485_send()
{ 
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);
}

#define USART2_RS485_IRQ_PRIORITY 0
void usart_config(uint8_t port, uint32_t baud, uint16_t data_bits, uint16_t parity)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
	
	GPIO_Initure.Pin  = GPIO_PIN_2; 		//PA2
	GPIO_Initure.Mode = GPIO_MODE_AF_PP;	//复用推挽输出
	GPIO_Initure.Pull = GPIO_PULLUP;		//上拉
	GPIO_Initure.Speed= GPIO_SPEED_HIGH;	//高速
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA2
	
	GPIO_Initure.Pin  = GPIO_PIN_3; 		//PA3
	GPIO_Initure.Mode = GPIO_MODE_AF_INPUT;	//复用输入
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA3
	
    GPIO_Initure.Pin  = GPIO_PIN_7; 		//PA7
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;//推挽输出
    GPIO_Initure.Pull = GPIO_PULLUP;        //上拉
    GPIO_Initure.Speed= GPIO_SPEED_HIGH;    //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
		
	/*初始化usart2*/
    __HAL_RCC_USART2_CLK_ENABLE();
	USART2_RS485Handler.Instance       = USART2;			    //USART2
	USART2_RS485Handler.Init.BaudRate  = baud;		            //波特率
	USART2_RS485Handler.Init.WordLength= UART_WORDLENGTH_8B;    //字长为8位数据格式
	USART2_RS485Handler.Init.StopBits  = UART_STOPBITS_1;	    //一个停止位
	USART2_RS485Handler.Init.Parity    = UART_PARITY_NONE;	    //无奇偶校验位
	USART2_RS485Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;	//无硬件流控
	USART2_RS485Handler.Init.Mode      = UART_MODE_TX_RX;		//收发模式
	HAL_UART_Init(&USART2_RS485Handler);			            //HAL_UART_Init()会使能USART2
    
	HAL_NVIC_EnableIRQ(USART2_IRQn);				            //使能USART1中断
	HAL_NVIC_SetPriority(USART2_IRQn,USART2_RS485_IRQ_PRIORITY,0);
}

void usart_send_byte(void *buf, uint16_t buf_len)
{
    HAL_UART_Transmit(&USART2_RS485Handler,buf,buf_len,HAL_MAX_DELAY);
}

uint8_t usart_get_byte(void)
{
	uint8_t data;
    HAL_UART_Receive(&USART2_RS485Handler,&data,1,HAL_MAX_DELAY);
	return data;
}

void usart_rx_it(BOOL sw) //是否开启接收中断
{
    if(sw){
	   __HAL_UART_ENABLE_IT(&USART2_RS485Handler,UART_IT_RXNE);
	}else{
	   __HAL_UART_DISABLE_IT(&USART2_RS485Handler,UART_IT_RXNE);
	}
}

void usart_tx_it(BOOL sw) //是否开启发送中断
{
    if(sw){
	   __HAL_UART_ENABLE_IT(&USART2_RS485Handler,UART_IT_TXE);
	}else{
	   __HAL_UART_DISABLE_IT(&USART2_RS485Handler, UART_IT_TXE);
	}
}

extern void prvvUARTTxReadyISR( void );
extern void prvvUARTRxISR( void );
void USART2_IRQHandler(void)
{
	 /*UART_IT_TXE pending bit由向data寄存器的写入来清除
	   UART_IT_RXNE pending bit由读取data寄存器来清除
	  */
    if(__HAL_UART_GET_IT_SOURCE(&USART2_RS485Handler,UART_IT_TXE)){
	   prvvUARTTxReadyISR();
	}else if(__HAL_UART_GET_IT_SOURCE(&USART2_RS485Handler,UART_IT_RXNE)){
	   prvvUARTRxISR();
	}
}

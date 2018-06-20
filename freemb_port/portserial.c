/* ----------------------- Port includes ------------------------------------*/
#include "stm32f1xx.h"
#include "usart2.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- static functions ---------------------------------*/
extern void open_485_send( void );
extern void close_485_send( void );


/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    /* If xRXEnable enable serial receive interrupts. If xTxENable enable
     * transmitter empty interrupts.
     */
	  if (xRxEnable){
          usart_rx_it(TRUE);
	  }else{
          usart_rx_it(FALSE);
	  }
	
	  if (xTxEnable){
	     open_485_send();
         usart_tx_it(TRUE);
	  }else{
	     close_485_send();
	     usart_tx_it(FALSE);
	  }
}

BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
	  u16 usart_parity;
	  u16 usart_data_bits;
	
	  if(eParity == MB_PAR_NONE){
		 usart_parity = UART_PARITY_NONE;
	  }else if(eParity == MB_PAR_ODD){
		 usart_parity = UART_PARITY_ODD;  
	  }else if(eParity == MB_PAR_EVEN){
		 usart_parity = UART_PARITY_EVEN;
	  }
		
	  usart_data_bits = UART_WORDLENGTH_8B;
	  
      usart_config(ucPORT, ulBaudRate, usart_data_bits, usart_parity); //ucDataBits固定为8位，应用层主要设置端口，波特率，校验位
	
      return TRUE;
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    /* Put a byte in the UARTs transmit buffer. This function is called
     * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
     * called. */
	  usart_send_byte(&ucByte,1);
	
	  return TRUE;
}

BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
    /* Return the byte in the UARTs receive buffer. This function is called
     * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
     */
	  *pucByte = usart_get_byte();
      return TRUE;
}

/* Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
void prvvUARTTxReadyISR( void )
{
     pxMBFrameCBTransmitterEmpty(  );
}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
void prvvUARTRxISR( void )
{
     pxMBFrameCBByteReceived(  );
}


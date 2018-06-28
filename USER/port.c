#include "stm32f1xx.h"
#include "mb.h"
#include "hci.h"

#define SHELVES_MAX_SLOTS_PERLAYER (50)

#define	usRegInputStart			   (0)
#define	REG_INPUT_START			   (0)
#define	REG_INPUT_NREGS			   SHELVES_MAX_SLOTS_PERLAYER

#define	usRegHoldingStart		   (0)
#define	REG_HOLDING_START		   (0)
#define	REG_HOLDING_NREGS		   SHELVES_MAX_SLOTS_PERLAYER

#define	REG_COILS_START			   (0)
#define	REG_COILS_SIZE			   (1)
#define	REG_COILS_NREGS			   (1)

u16	usRegInputBuf[REG_INPUT_NREGS];
u16	usRegHoldingBuf[REG_HOLDING_NREGS];
u16 ucRegCoilsBuf[REG_COILS_NREGS];

eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
	eMBErrorCode    eStatus = MB_ENOERR;
	int             iRegIndex;
	
    if( ( (int16_t)usAddress >= REG_INPUT_START )&& ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) ){
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 ){
            *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }else{
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;
    
    static uint8_t count = 0;
    
    if( ( (int16_t)usAddress >= REG_HOLDING_START ) && ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegHoldingStart );
        switch ( eMode )
        {
        case MB_REG_READ:
            while( usNRegs > 0 )
            {
				*pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] >> 8 );
				*pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] & 0xFF );
				iRegIndex++;
                usNRegs--;
            }
            break;

        case MB_REG_WRITE:
            /*while( usNRegs > 0 )
            {

				usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
				usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
				iRegIndex++;
                usNRegs--;
            }

            if(*(pucRegBuffer+1) == 3){
            
                count++;
                if(count == 5){
                   count == 0;
                }
            }*/
            
            hci_do_led(usAddress,*(pucRegBuffer+1));
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    
    return eStatus;
}

eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
	eMBErrorCode eStatus = MB_ENOERR;//´íÎó×´Ì¬
	u16 iNCoils = ( u16 )usNCoils;   //¼Ä´æÆ÷¸öÊý
	u16 usBitOffset;//¼Ä´æÆ÷Æ«ÒÆÁ¿

	//¼ì²é¼Ä´æÆ÷ÊÇ·ñÔÚÖ¸¶¨·¶Î§ÄÚ
	if( ( (u16)usAddress >= REG_COILS_START ) &&( usAddress + usNCoils <= REG_COILS_START + REG_COILS_SIZE ) ){
		  //¼ÆËã¼Ä´æÆ÷Æ«ÒÆÁ¿
		usBitOffset = ( int16_t )( usAddress - REG_COILS_START );
			
		switch ( eMode ){
		 
		  case MB_REG_READ:  //¶Á²Ù×÷
				
				  while( iNCoils > 0 ){
						
						 //TODO task
					 *pucRegBuffer++ = xMBUtilGetBits((UCHAR *) ucRegCoilsBuf, usBitOffset,( uint8_t )( iNCoils > 8 ? 8 : iNCoils ) );
					 iNCoils -= 8;
					 usBitOffset += 8;
				}
		  
					break;

		case MB_REG_WRITE: //Ð´²Ù×÷
	
				  /*while( iNCoils > 0 ){
					
					 xMBUtilSetBits((UCHAR *) ucRegCoilsBuf, usBitOffset,( uint8_t )( iNCoils > 8 ? 8 : iNCoils ),*pucRegBuffer++ );
					 iNCoils -= 8;
					 usBitOffset += 8;
					
					 //TODO task
				  }*/
				
				break;
	   }

    }else{
		eStatus = MB_ENOREG;
    }
	
    return eStatus;
}

//¶Á¿ª¹Ø¼Ä´æÆ÷ 0x02
eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    ( void )pucRegBuffer;
    ( void )usAddress;
    ( void )usNDiscrete;
    return MB_ENOREG;
}

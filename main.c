/******************************************************************************
 *******************************copyright**************************************
 ******************************************************************************/

/******************************************************************************
 *
 * 		Author	: Xuzhi Liu
 * 		Date	: 2019.03.11
 * 		Brief	: CC115L/CC1101������Ƶ�շ�ͨ��
 * 		Version	: 1.0.0
 *
 * 			˵	��:����оƬ�ĸ��ù���ѡ�񣬵���Ӧ��оƬ�����ֲ������
 *
 *
 * 			History
 * 					1.Author	: Xuzhi Liu
 * 					  Date		: 2019.03.11
 * 					  Mod		: 1.���ڿ�汾��CC115L,�޸�Ϊ�Ĵ����档
 *
 *
 * 					  		Ӳ������:
 * 					  			  		   SPI_CLK  --> P4.2
 * 					  			  		   SPI_CS   --> P4.3
 * 					  			  		   SPI_MOSI --> P4.0
 * 					  			  		   SPI_MISO --> P4.1
 *
 *
 *					2.Author	: Xuzhi Liu
 * 					  Date		: 2019.03.13
 * 					  Mod		: ����ʱ�������Ĳ��Դ���
 *
 ***********************************************************************************/

#include "msp430fr6989.h"
#include "bsp_spi.h"
#include "bsp_delay.h"
#include "bsp_cc1101.h"
#include "bsp_led.h"
#include "_msp430fr6989_lanchpad.h"
#include "_ASK_WRITE.h"
#include "_PMM_1_X.h"



int main(void)
{

	uint8_t Tx_Buffer[5]={0x59,0x02,0x32,0x04,0x22};   //����Ҫ���͵�����
//	uint8_t Tx_ON[5]={0x59,0x02,0x32,0x04,0x25};   		//����Ҫ���͵�����
//	uint8_t Tx_OFF[5]={0x59,0x02,0x32,0x05,0x26};   	//����Ҫ���͵�����
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

/*-------------------------------����ʦ�������������-----------------------------------------*/
	_MCU_LPM_Set_(_PMM1X_IO_Start);        // Low Power Set -- all port set to GND output(LEDL on)
/*-----------------------------------------------------------------------------------------*/

    GPIO_InitConfig();
//    LED_Config();
    SPI_Init();
//	CC1101_Reset();
//	Write_CMD(SRES);
	CC1101_Init();
	Write_CMD(SFTX);
	CC1101_RFDataPack_Send(Tx_Buffer, sizeof(Tx_Buffer));

/*	while(1)
	{

	}*/

//���ڲ���CC115L/CC1101�Ĺ���ʱ�� (Ӳ�����ӣ���Ƶģ�����P1.0��LED1�����°���1.P1.1��ʼ����)
#if		0
	while((P1IN&BIT1))
		{
			P1OUT &=~ BIT0;
		}

		while((P1IN & BIT1) == 0 )
		{
			P1OUT |= BIT0;
			Delay_us(400);
			CC1101_Reset();
			CC1101_Init();
			Write_CMD(SFTX);
			CC1101_RFDataPack_Send(Tx_Buffer, sizeof(Tx_Buffer));
			P1OUT &=~ BIT0;
			break;
		}
#endif

/*-------------------------------����ʦ�������������-----------------------------------------*/
	_PMM1X_IO_End();
/*-----------------------------------------------------------------------------------------*/
	
}

/******************************************************************************
 *******************************copyright**************************************
 ******************************************************************************/

/******************************************************************************
 *
 * 		Author	: Xuzhi Liu
 * 		Date	: 2019.03.11
 * 		Brief	: CC115L/CC1101无线射频收发通信
 * 		Version	: 1.0.0
 *
 * 			说	明:关于芯片的复用功能选择，到对应的芯片数据手册里查找
 *
 *
 * 			History
 * 					1.Author	: Xuzhi Liu
 * 					  Date		: 2019.03.11
 * 					  Mod		: 1.基于库版本的CC115L,修改为寄存器版。
 *
 *
 * 					  		硬件连接:
 * 					  			  		   SPI_CLK  --> P4.2
 * 					  			  		   SPI_CS   --> P4.3
 * 					  			  		   SPI_MOSI --> P4.0
 * 					  			  		   SPI_MISO --> P4.1
 *
 *
 *					2.Author	: Xuzhi Liu
 * 					  Date		: 2019.03.13
 * 					  Mod		: 增加时长及功耗测试代码
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

	uint8_t Tx_Buffer[5]={0x59,0x02,0x32,0x04,0x22};   //定义要发送的数据
//	uint8_t Tx_ON[5]={0x59,0x02,0x32,0x04,0x25};   		//定义要发送的数据
//	uint8_t Tx_OFF[5]={0x59,0x02,0x32,0x05,0x26};   	//定义要发送的数据
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

/*-------------------------------黄瑞师兄能量管理代码-----------------------------------------*/
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

//用于测试CC115L/CC1101的工作时间 (硬件连接：射频模块接于P1.0即LED1，按下按键1.P1.1开始工作)
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

/*-------------------------------黄瑞师兄能量管理代码-----------------------------------------*/
	_PMM1X_IO_End();
/*-----------------------------------------------------------------------------------------*/
	
}

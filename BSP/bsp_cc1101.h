/*
 * bsp_cc1101.h
 *
 *  Created on: 2018��11��30��
 *      Author: xu
 */

#ifndef BSP_BSP_CC1101_H_
#define BSP_BSP_CC1101_H_

#include "msp430fr6989.h"
#include "bsp_delay.h"
#include "bsp_spi.h"
#include "bsp_led.h"

/*
**	˵�������е������CC115L ��CC1101�ֲ�
 *	IDLE������״̬
*/


//����д����ȡ��ʽ
#define		WRITE_SINGLE		0x00						//���ֽ�д��
#define 	WRITE_BURST     	0x40						//����д��
#define 	READ_SINGLE     	0x80						//���ֽڶ�ȡ
#define 	READ_BURST      	0xC0						//������ȡ


#define     READ_BURST_FIFO     0xFF        //ͻ����ȡRX FIFO
#define     READ_SINGLE_FIFO    0xBF        //���ֽڶ�ȡ RX FIFO
#define     WRITE_BURST_FIFO    0x7F        //ͻ��дTX FIFO
#define     WRITE_SINGLE_FIFO   0x3F        //���ֽ�д TX FIFO


//PATABLE��ȡ
#define     READ_BURST_PATABLE     0xFE        //ͻ����ȡPATABLE
#define     READ_SINGLE_PATABLE    0xBE        //���ֽڶ�ȡ RX FIFO
#define     WRITE_BURST_PATABLE    0x7E        //ͻ��дTX FIFO
#define     WRITE_SINGLE_PATABLE   0x3E        //���ֽ�д TX FIFO

/*******************************ѡͨ�Ĵ�����ַ(д��ַ)��13����**********************************
	*	��������Щ�Ĵ���ʱ����ʹ�ڲ�״̬��ģʽ�����ı�
	*	bit7,R(1),����ַ����0x20ʱ,bit6����Ϊͻ��λ��bit6 --1,ʱΪ״̬��bit6 --0ʱΪѡͨ

*/
#define		SRES				0x30						//��λоƬ
#define		SFSTXON				0x31						//������У׼Ƶ�ʺϳ���
#define		SXOFF				0x32						//�رվ�������
#define		SCAL				0x33						//У׼Ƶ�ʺϳ���������ر�
#define		SRX					0x34						//���� RX
#define		STX					0x35						//����TXģʽ(д)
#define		SIDLE				0x36						//�˳� RX/TX ģʽ,����SIDLE ָ��ѡͨ������ǿ�����߿��������� IDLE ״̬
#define		SWOR				0x38						//�� WORCTRL.RC_PD=0,�������Զ� RX��ѯ���У����߻��ѣ�
#define		SPWD				0x39						//�� CSn Ϊ�ߵ�ƽʱ����ϵ�ģʽ(����ģʽ)
#define		SFRX				0x3A						//ˢ ��RXFIFO������,����IDLE��RXFIFO_OVERFLOW״̬�²ŷ���SFRX
#define		SFTX				0x3B						//ˢ ��TXFIFO������,����IDLE��TXFIFO_OVERFLOW״̬�²ŷ���SFTX
#define		SWORRST				0x3C						//��λʵʱʱ��Ϊ�¼� 1 ֵ



/*******************************8λͨ��(��׼)��ַ(�ɶ���д��ַ,���ﶨ��д��ַ)��47����**********************************
	*	���Ҫ��ȡ�����ԶԵ�ǰָ��ֱ��(����)&0x80(���ֽڶ�ȡ)
	*	bit7,R(1),����ַ����0x20ʱ,bit6����Ϊͻ��λ��bit6 --1,ʱΪ״̬��bit6 --0ʱΪѡͨ
*/

#define     IOCFG2_ADDR			0x00						//GDO2���ֽ�д��ַ
#define     IOCFG1_ADDR			0x01						//GDO1���ֽ�д��ַ,����MISO,Ĭ��ע�͵�,������ͨIO��
#define     IOCFG0_ADDR			0x02						//GDO0���ֽ�д��ַ
#define     FIFOTHR				0x03						//RX FIFO �� TX FIFO ��ֵ
#define     SYNC1				0x04						//ͬ���֣����ֽ�
#define     SYNC0				0x05						//ͬ���֣����ֽ�
#define     PKTLEN				0x06						//���ݰ�����
#define     PKTCTRL1			0x07						//���ݰ��Զ�����
#define     PKTCTRL0			0x08						//���ݰ��Զ�����
#define     ADDR				0x09						//������ַ
#define     CHANNR				0x0A						//�ŵ�����
#define     FSCTRL1				0x0B						//Ƶ�ʺϳ�������
#define     FSCTRL0				0x0C						//Ƶ�ʺϳ�������
#define     FREQ2				0x0D						//Ƶ�ʿ����֣����ֽ�
#define     FREQ1				0x0E						//Ƶ�ʿ����֣��м��ֽ�
#define     FREQ0				0x0F						//Ƶ�ʿ����֣����ֽ�
#define     MDMCFG4				0x10						//���ƽ��������
#define     MDMCFG3				0x11						//���ƽ��������
#define     MDMCFG2				0x12						//���ƽ��������
#define     MDMCFG1				0x13						//���ƽ��������
#define     MDMCFG0				0x14						//���ƽ��������
#define     DEVIATN				0x15						//���ƽ����ƫ������
#define     MCSM2				0x16						//�����߿���״̬������
#define     MCSM1				0x17						//�����߿���״̬������
#define     MCSM0				0x18						//�����߿���״̬������
#define     FOCCFG				0x19						//Ƶ��ƫ�Ʋ�������
#define     BSCFG				0x1A						//λͬ������
#define     AGCTRL2				0x1B						//AGC ����
#define     AGCTRL1				0x1C						//AGC ����
#define     AGCTRL0				0x1D						//AGC ����
#define     WOREVT1				0x1E						//���ֽ��¼� 0 ��ʱ
#define     WOREVT0				0x1F						//���ֽ��¼� 0 ��ʱ
#define     WORCTRL				0x20						//���߻��ѿ���
#define     FREND1				0x21						//ǰ�� RX ����
#define     FREND0				0x22						//ǰ�� TX ����
#define     FSCAL3				0x23						//Ƶ�ʺϳ���У׼
#define     FSCAL2				0x24						//Ƶ�ʺϳ���У׼
#define     FSCAL1				0x25						//Ƶ�ʺϳ���У׼
#define     FSCAL0				0x26						//Ƶ�ʺϳ���У׼
#define     RCCTRL1				0x27						//RC ��������
#define     RCCTRL0				0x28						//RC ��������
#define     FSTEST				0x29						//Ƶ�ʺϳ���У׼����,���ý���д����
#define     PTEST				0x2A						//��������
#define     AGCTEST				0x2B						//AGC ����,���ý���д����
#define     TEST2    			0x2C						//���ֲ�������
#define     TEST1				0x2D						//���ֲ�������
#define     TEST0				0x2E						//���ֲ�������

#define		PATABLE				0x3E						//������ʿ���


//����ͨ���������ֵ
#define     GDO_LOW				0x00						//�����ֲᣬ0x00����,bit7 ����,bit6 �ж�����ߵ͵�ƽ
#define     GDO_HIGH			0X40						//����ߵ�ƽ

						//bit7,R(1),����ַ����0x20ʱ,bit6����Ϊͻ��λ��bit6 --1,ʱΪ״̬��bit6 --0ʱΪѡͨ

/*******************************״̬�Ĵ�����ַ(����ַ)��ֻ�ܶ�(12��)��**********************************
	*	bit7,R(1),����ַ����0x20ʱ,bit6����Ϊͻ��λ��bit6 --1,ʱΪ״̬��bit6 --0ʱΪѡͨ
*/

#define		PARTNUM				0xF0				//оƬ�����Ŀ��ַ
#define		VERSION				0xF1				//��ȡ�汾ָ���ַ
#define		FREQEST				0xF2				//Ƶ��ƫ�ƹ���
#define		LQI					0xF3				//��·�������������
#define		RSSI				0xF4				//�����ź�ǿ��ָʾ��ַ
#define		MARCSTATE			0xF5				//�����߿���״̬��״̬��ַ
#define		WORTIME1			0xF6				//WOR ��ʱ�����ֽ�
#define		WORTIME0			0xF7				//WOR ��ʱ�����ֽ�
#define		PKTSTATUS			0xF8				//��ǰ GDOx ״̬�����ݰ�״̬
#define		VCO_VC_DAC			0xF9				//PLL У׼ģ��ĵ�ǰ����
#define		TXBYTES				0xFA				//TX FIFO �е�������ֽ���
#define		RXBYTES				0xFB				//RX FIFO �е�������ֽ���
#define		RCCTRL1_STATUS		0xFC				//���� RC ����У׼���
#define		RCCTRL0_STATUS		0xFD				//���� RC ����У׼���



//�������ݰ�����
#define		DATA_LEN			255					//�������ݰ�����


void Write_CMD(uint8_t CMD);
void Write_Data(uint8_t Write_Addr,uint8_t Write_data);
void Write_burst(uint8_t Write_Addr,uint8_t *pbuffer,uint8_t Length);
void CC1101_Reset(void);
void CC1101_Init(void);
void WriteTxFITO(uint8_t * pBuffer,uint8_t len);
void CC1101_RFDataPack_Send(uint8_t *pBuff, uint16_t len);

#endif /* BSP_BSP_CC1101_H_ */

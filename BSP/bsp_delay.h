/*
 * bsp_delay.h
 *
 *  Created on: 2018��12��1��
 *      Author: xu
 *      ˵	��:����MSP430��Ƭ��ʹ��__delay_cycles��ʱ������.
 *				IAR for MSP430�������ṩ��һ�������������ľ�ȷ��ʱ����(����������
 *				����)���ṩ�û���ȷ��ʱʹ��, �ú���ԭ����:
 *				__intrinsic void __delay_cycles(unsigned long __cycles);
 *				���ڲ�����ʵ��__cycles��CPU���ڵ���ʱ,�����ڸò���������,��Ҫ����һ��:
 *				__cycles��Ҫ���Ǵ��ݵ���CPU���е����ڸ���
 *
 *				�����ձ���÷���:
 *				#define CPU_CLOCK 8000000
 *				#define delay_us(us) __delay_cycles(CPU_CLOCK/1000000*(us))
 *				#define delay_ms(ms) __delay_cycles(CPU_CLOCK/1000*(ms))
 *
 *				��CPU��ʱ��Ƶ��Ϊ8MHzʱ, ��ȷʵû������, ����������д��:
 *				#define CPU_CLOCK 8000000
 *				��������������뵽, ����ͨ���޸�����ֵ��ʵ�ֶԲ�ͬ��Ƶϵͳ������ͳһ,��ʵ
 *				���ǲ���ȷ��! �����޸�Ϊ#define CPU_CLOCK 32768��ʵ��32KHz��Ƶ����ʱ...
 *
 *				���������㿴��:
 *				��ϵͳ��ʱ��Ƶ��CPU_CLOCKΪ8MHzʱ:
 *				Ƶ�� f = 8MHz = 8,000,000Hz
 *				�������� Tm = 1/f = 1/8MHz = 1/8us
 *				Ҳ����˵,һ����������(nop)��ʱ����1/8us,������ʱ1us��8*Tm,ͬ����:
 *				#define delay_us(us) __delay_cycles(8*(us))
 *				#define delay_ms(ms) __delay_cycles(8000*(ms))
 *
 *				��������ĺ궨�巽��,���ǰ�CPU_CLOCK�����32768,��ô:
 *				Ƶ�� f = 32KHz = 32,768Hz
 *				�������� Tm = 1/f = 1/32768Hz ~= 30.5us
 *				�����֪,CPU��̵�ָ��ִ������Ϊ30.5us, ��ʱ, ����ʱ1us, �������?
 *				����, �򵥵ذ�����Ķ���ĳ�
 *				#define CPU_CLOCK 32768
 *				�Ǿ��Դ����.
 *
 *				ͬ��, ����Щ����ʵ����0.5us����ʱ, ���ڵ�f = 1MHz = 1000000HzʱҲ
 *				�ǲ���ʵ��, ��ʱ��������Tm = 1us. ��f = 8Mhzʱ, 4����������Ϊ0.5us�п�.
 *
 *				����, Ϊ������������ʹ�û���ȷ�����,������������������:
 *				#if CPU_CLOCK == 8000000
 *				#define delay_us(us) __delay_cycles(8*(us))
 *				#define delay_ms(ms) __delay_cycles(8000*(ms))
 *				#else
 *				#pragma error "CPU_CLOCK is defined implicitly!"
 *				#endif
 *
 *				����:
 *����				  __delay_cycles �����������ĺ���, ֻ���ṩ����������չ��,�ú�����
 *				��֧�ֱ�������, �����ֻ���ǳ���.
 */

#ifndef BSP_BSP_DELAY_H_
#define BSP_BSP_DELAY_H_

#include "msp430fr6989.h"

#define CPU_CLOCK		1000000			//1MHz
#define Delay_us(us)	 __delay_cycles(CPU_CLOCK/1000000*(us))
#define Delay_ms(ms) 	 __delay_cycles(CPU_CLOCK/1000*(ms))

typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;

#endif /* BSP_BSP_DELAY_H_ */

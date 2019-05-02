/*
 * bsp_spi.h
 *
 *  Created on: 2018年11月30日
 *      Author: xu
 *      使用USCI_B1的 SPI功能
 */

#ifndef BSP_BSP_SPI_H_
#define BSP_BSP_SPI_H_

#include "msp430fr6989.h"
#include "bsp_delay.h"

//CS引脚宏定义
#define  SPI_CS_PIN			BIT3

//CLK引脚宏定义
#define  SPI_CLK_PIN		BIT2

//MISO引脚宏定义
#define  SPI_MISO_PIN		BIT1

//MOSI引脚宏定义
#define  SPI_MOSI_PIN		BIT0

void SPI_CS_HIGH(void);
void SPI_CS_LOW(void);

void SPI_Init(void);
uint8_t SPI_Send(uint8_t data);

#endif /* BSP_BSP_SPI_H_ */

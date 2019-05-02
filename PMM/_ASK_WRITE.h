/*
 * _ASK_WRITE.h
 *  HR2018.11.29
 */

#ifndef _ASK_WRITE_H_
#define _ASK_WRITE_H_

#include "_msp430fr6989_lanchpad.h"

struct S_ASK__WRITE_DATA {
    unsigned char*  data;       // data value
    unsigned int    data_len;   // data number (per bit)
    unsigned int    bitT;       // time of each bit
    unsigned char   protocol;   // write protocol (based on the form of each bit)
};

#define D_ASK__LEADCODE_TIME 10              // *30 = 300us
#define D_ASK__BIT_TIME_10k8    3
#define D_ASK__BIT_TIME_8k1     4
#define D_ASK__BIT_TIME_3k6     9
#define D_ASK__BIT_TIME_2k5     14

#define D_ASK__PROTOCOL_0 0             // protocol 0
#define D_ASK__PROTOCOL_1 1             // protocol 1
#define D_ASK__PROTOCOL_2 2             // protocol 2
#define D_ASK__PROTOCOL_3 3             // protocol 3

#define _ASK_WP_H    P9OUT |= BIT2
#define _ASK_WP_L    P9OUT &= ~BIT2
#define _ASK_WP_SET  P9DIR |= BIT2

void _ASK_Write_Init_();
void _ASK_Write_FRAME_(struct S_ASK__WRITE_DATA *pre_data, struct S_ASK__WRITE_DATA *data);
#endif /* _ASK_WRITE_H_ */

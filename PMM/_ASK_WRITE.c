/*
 * _ASK_WRITE.c
 *  HR2018.11.29
 */

#include "_ASK_WRITE.h"

/*************************************************************
 * name:        _ASK_Write_Init_
 * function:    ASK write, port init(Data_Port set to low output)
 * input:       void
 * output:      void
 *************************************************************/
void _ASK_Write_Init_()
{
    _ASK_WP_SET;
    _ASK_WP_L;
}

/*************************************************************
 * name:        _ASK_Write_BITP0_
 * function:    ASK write, bit, basic protocal
 * input:       unsigned char data :    data storge room
 *              unsigned char mask :    bit mask
 *              unsigned int  bitT :    bit time
 * output:      void
 *************************************************************/
//protocol 0 (0:0; 1:1)
#define _ASK_Write_BITP0_(data, mask, bitT) \
{\
    if(data & mask)\
    {\
        _ASK_WP_H;\
        _MCU_T0_Delay30us(bitT);\
    }\
    else\
    {\
        _ASK_WP_L;\
        _MCU_T0_Delay30us(bitT);\
    }\
}

//protocol 1 (0:100; 1:110)
#define _ASK_Write_BITP1_(data, mask, bitT) \
{\
    _ASK_WP_H;\
    _MCU_T0_Delay30us(bitT);\
    \
    if(data & mask)\
        _ASK_WP_H;\
    else\
        _ASK_WP_L;\
    _MCU_T0_Delay30us(bitT);\
    \
    _ASK_WP_L;\
    _MCU_T0_Delay30us(bitT);\
}

//protocol 2 (0:10; 1:100)
#define _ASK_Write_BITP2_(data, mask, bitT) \
{\
    _ASK_WP_H;\
    _MCU_T0_Delay30us(bitT);\
    \
    if(data & mask)\
    {\
        _ASK_WP_L;\
        _MCU_T0_Delay30us(bitT);\
    }\
    \
    _ASK_WP_L;\
    _MCU_T0_Delay30us(bitT);\
}
/*************************************************************
 * name:        _ASK_Write_BYTE_
 * function:    ASK write, byte, send 8 bit or less once
 * input:       unsigned char    data     :   data value
 *              unsigned int     bit_len  :   bit length <= 8
 *              unsigned int     bitT     :   bit time
 * output:      void
 *************************************************************/
// protocol 0
#define _ASK_Write_BYTEP0_(data, bit_len, bitT) \
{\
    switch(bit_len)\
    {\
        case 8: _ASK_Write_BITP0_(data, 0x80, bitT);\
        case 7: _ASK_Write_BITP0_(data, 0x40, bitT);\
        case 6: _ASK_Write_BITP0_(data, 0x20, bitT);\
        case 5: _ASK_Write_BITP0_(data, 0x10, bitT);\
        case 4: _ASK_Write_BITP0_(data, 0x08, bitT);\
        case 3: _ASK_Write_BITP0_(data, 0x04, bitT);\
        case 2: _ASK_Write_BITP0_(data, 0x02, bitT);\
        case 1: _ASK_Write_BITP0_(data, 0x01, bitT); break;\
        default: break;\
    }\
}
// protocol 1
#define _ASK_Write_BYTEP1_(data, bit_len, bitT) \
{\
    switch(bit_len)\
    {\
        case 8: _ASK_Write_BITP1_(data, 0x80, bitT);\
        case 7: _ASK_Write_BITP1_(data, 0x40, bitT);\
        case 6: _ASK_Write_BITP1_(data, 0x20, bitT);\
        case 5: _ASK_Write_BITP1_(data, 0x10, bitT);\
        case 4: _ASK_Write_BITP1_(data, 0x08, bitT);\
        case 3: _ASK_Write_BITP1_(data, 0x04, bitT);\
        case 2: _ASK_Write_BITP1_(data, 0x02, bitT);\
        case 1: _ASK_Write_BITP1_(data, 0x01, bitT); break;\
        default: break;\
    }\
}

// protocol 2
#define _ASK_Write_BYTEP2_(data, bit_len, bitT) \
{\
    switch(bit_len)\
    {\
        case 8: _ASK_Write_BITP2_(data, 0x80, bitT);\
        case 7: _ASK_Write_BITP2_(data, 0x40, bitT);\
        case 6: _ASK_Write_BITP2_(data, 0x20, bitT);\
        case 5: _ASK_Write_BITP2_(data, 0x10, bitT);\
        case 4: _ASK_Write_BITP2_(data, 0x08, bitT);\
        case 3: _ASK_Write_BITP2_(data, 0x04, bitT);\
        case 2: _ASK_Write_BITP2_(data, 0x02, bitT);\
        case 1: _ASK_Write_BITP2_(data, 0x01, bitT); break;\
        default: break;\
    }\
}
/*************************************************************
 * name:        _ASK_Write_GROUP_
 * function:    ASK write, group, send serval bytes once
 * input:       struct S_ASK__WRITE_DATA *data
 * output:      void
 *************************************************************/
void _ASK_Write_GROUP_(struct S_ASK__WRITE_DATA *data)
{
    int i;

    unsigned int byte_len = data->data_len >> 3;        //full byte_len
    unsigned int bit_len = data->data_len & 0x0007;     //rest bit_len

    switch(data->protocol)
    {
        case D_ASK__PROTOCOL_1:
            for(i = byte_len; i > 0; i--)
            {
                _ASK_Write_BYTEP1_(*(data->data+byte_len-i), 8, data->bitT);
            }
            break;

        case D_ASK__PROTOCOL_2:
            for(i = byte_len; i > 0; i--)
            {
                _ASK_Write_BYTEP2_(*(data->data+byte_len-i), 8, data->bitT);
            }
            break;

        default:
            for(i = byte_len; i > 0; i--)
            {
                _ASK_Write_BYTEP0_(*(data->data+byte_len-i), 8, data->bitT);
            }
            break;
    }
    _ASK_Write_BYTEP0_(*(data->data+byte_len), bit_len, data->bitT);
}

/*************************************************************
 * name:        _ASK_Write_FRAME_
 * function:    ASK write, group, send serval bytes once
 * input:       struct S_ASK__WRITE_DATA *lead_code
 *              struct S_ASK__WRITE_DATA *data
 * output:      void
 *************************************************************/

void _ASK_Write_FRAME_(struct S_ASK__WRITE_DATA *lead_code, struct S_ASK__WRITE_DATA *data)
{
    // lead code
    _ASK_Write_GROUP_(lead_code);

    // data
    _ASK_Write_GROUP_(data);

    // end
    _ASK_WP_H;
    _MCU_T0_Delay30us(D_ASK__BIT_TIME_10k8);
    _ASK_WP_L;
    _MCU_T0_Delay30us(data->bitT*6);
}




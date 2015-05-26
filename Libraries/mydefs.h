#ifndef _MYDEFS_H
#define _MYDEFS_H

/*
 * This file contains the definitions of the bytes used for communication with
 * the STM32 Controller at the firmware level. (Firmware/serial level)
 */

#define STATE_ABORT             (uint8_t) 0
#define STATE_ACTIVE            (uint8_t) 1
#define STATE_IDLE              (uint8_t) 2
#define STATE_START             (uint8_t) 3
#define STATE_GOTO		(uint8_t) 4
#define STATE_SINGLE_MEAS	(uint8_t) 5
#define STATE_SEND_POS		(uint8_t) 6
#define STATE_RESET		(uint8_t) 7

#define OUT_CMD_FIRSTPIXEL      (uint8_t) 1
#define OUT_CMD_LASTPIXEL       (uint8_t) 2
#define OUT_CMD_SCANNING        (uint8_t) 3
#define OUT_CMD_DAC             (uint8_t) 4
#define OUT_CMD_CHAN            (uint8_t) 5
#define OUT_CMD_START           (uint8_t) 6

#define IN_CMD_ABORT            (uint8_t) 0
#define IN_CMD_GOTO             (uint8_t) 1
#define IN_CMD_START            (uint8_t) 2
/* These are comprehended by IN_CMD_GOTO and
 * are not duplicated (hence commented out)
#define IN_CMD_SET_DACX         (uint8_t) 3
#define IN_CMD_SET_DACY         (uint8_t) 4
#define IN_CMD_SET_DACZ         (uint8_t) 5
#define IN_CMD_SET_DACAUX       (uint8_t) 6
*/
#define IN_CMD_GET_DAC          (uint8_t) 7
#define IN_CMD_GET_CHAN         (uint8_t) 8
#define IN_CMD_SET_START        (uint8_t) 9
#define IN_CMD_SET_PIXELS       (uint8_t) 10
#define IN_CMD_SET_TSETTLE      (uint8_t) 11
#define IN_CMD_SET_IINC         (uint8_t) 12
#define IN_CMD_SET_JINC         (uint8_t) 13
#define IN_CMD_RESET		(uint8_t) 14

#define USART_STATE_CMD         (uint8_t) 0
#define USART_STATE_SIZE        (uint8_t) 1
#define USART_STATE_PAYLOAD     (uint8_t) 2
#define USART_STATE_TIMEOUT	(uint8_t) 3
#define USART_STATE_FINISHED	(uint8_t) 4

#define STATE_MACHINE_INITPOS	(int32_t) 1

#endif

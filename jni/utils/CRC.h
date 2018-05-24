/*
 * CRC.h
 *
 *  Created on: 2018年4月27日
 *      Author: ning
 */

#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED


#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


#define RUNTTIME							0
#define TABLE								1
#define HARDWARE							2


/* ---------- Defines for 8-bit SAE J1850 CRC calculation (Not reflected) ------------------------------------------------------- */
#define CRC_8_RESULT_WIDTH                  8u
#define CRC_8_POLYNOMIAL                    0x1Du
#define CRC_8_INIT_VALUE                    0xFFu
#define CRC_8_XOR_VALUE                     0xFFu
#define CRC_8_MODE							RUNTTIME

/* ---------- Defines for 16-bit CCITT CRC calculation (Not reflected) ---------------------------------------------------------- */
#define CRC_16_RESULT_WIDTH                 16u
#define CRC_16_POLYNOMIAL                   0x1021u
#define CRC_16_INIT_VALUE                   0xFFFFu
#define CRC_16_XOR_VALUE                    0x0000u
#define CRC_16_MODE							RUNTTIME

/* ---------- Defines for 32-bit CCITT CRC calculation (Reflected) -------------------------------------------------------------- */
#define CRC_32_RESULT_WIDTH                 32u
#define CRC_32_POLYNOMIAL                   0x04C11DB7u
#define CRC_32_INIT_VALUE                   0xFFFFFFFFu
#define CRC_32_XOR_VALUE                    0xFFFFFFFFu
#define CRC_32_MODE							RUNTTIME



void CRC_Init(void);

/**
 * This function makes a CRC8 calculation on Length data bytes with SAEJ1850 parameters
 *
 * RETURN VALUE: 8 bit result of CRC calculation
 */
uint8_t CRC_CalculateCRC8(const uint8_t *Buffer, uint8_t Length);

/**
 * This function makes a CRC16 calculation on Length data bytes
 *
 * RETURN VALUE: 16 bit result of CRC calculation
 */
uint16_t CRC_CalculateCRC16(const uint8_t *Buffer, uint8_t Length);

/**
 * This function makes a CRC32 calculation on Length data bytes
 *
 * RETURN VALUE: 32 bit result of CRC calculation
 */
uint32_t CRC_CalculateCRC32(const uint8_t *Buffer, uint8_t Length);


#ifdef __cplusplus
}
#endif


#endif // CRC_H_INCLUDED

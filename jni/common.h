/*
 * common.h
 *
 *  Created on: 2018年4月25日
 *      Author: ning
 */

#ifndef COMMON_H_
#define COMMON_H_

#define GIT_VERSION "20180412-54d6fcc"
#define SDK_VERSION "V1.0.0"

typedef unsigned char uint8;
#include <string.h>

//#define LOG_TAG {frameDataHandle}
#ifndef NULL
#define NULL ((void*)0)
#endif
static uint8 common_data_header[]={0x79};
static uint8 common_data_footer[]={0xFE};
const unsigned int frame_type_size = 1;
const unsigned int cmd_id_size = 2;
const unsigned int data_len_size = 1;
const unsigned int frame_no_size = 1;
const unsigned int frame_sum_size = 1;
const unsigned int frame_crc_size = 1;
const unsigned int total_size = 73;
const unsigned int to_data_size = 5;

#endif /* COMMON_H_ */

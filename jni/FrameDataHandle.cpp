/*
 * FrameDataHandle.cpp
 *
 *  Created on: 2018年4月24日
 *      Author: ning
 */

#include "utils/parser.h"
#include "CRC.h"
#include "FrameDataHandle.h"
#include "debug.h"

#include <stdio.h>
//using namespace frameDataHandle;
/**
 * @data: 一帧完整数据
 * @return: 解析后的数据长度
 */
long getParserData(char* data, long data_len, char* reData) {
	CRC_Init();
	LOGINFO("FrameDataHandle: 进入CPP\n");
	if (data == NULL || (data_len <= 0)) {
		LOGERROR("帧数据为空，无法进行解析\n");
		return -1;
	} else {
		for (uint8 i=0;i<data_len;i++) {
			LOGINFO("0x%x ",data[i]);
			if ((i!=0) && (i%30 == 0)) {
				LOGINFO("/n");//够一定个数就换行
			}
		}
	}
//	uint8 _data[] = {0x79,0x00,0x03,0x01,0x11,0x00,0x01,0xFE};
//	for (uint8 i = 0; i < data_len; i++) {
//		LOGINFO("0x%x ", data[i]);
//		if ((i != 0) && (i % 30 == 0)) {
//			LOGINFO("/n"); //够一定个数就换行
//		}
//		LOGINFO("i=0x%x ", i);
//		LOGINFO("i=%d",i);
//	}
//	LOGINFO("frameDataHandle : sizeof(_data): %d\n", sizeof(_data));
	return getParserData(common_data_header, sizeof(common_data_header), common_data_footer, sizeof(common_data_footer), (uint8*)data, data_len);
}

/**
 * 获取解析后的帧数据
 *
 * @_data_header: 数据头指针
 * @_header_size: 数据头大小
 * @_data_footer: 数据尾指针
 * @_foot_size: 数据尾大小
 * @_data_frame_size: 一帧完整数据的大小
 *
 * @return: 解析数据
 */

long getParserData(uint8 *_data_header, uint8 _header_size, uint8 *_data_footer, uint8 _foot_size,
		uint8* data, long data_len) {
	LOGINFO("frameDataHandle : sizeof(_data): %d,0x%x\n", sizeof(data), sizeof(data));
	uint8* frame_sum = parser_before_init(_data_header, sizeof(common_data_header), _data_footer,
    		sizeof(_data_footer), data);

	if (frame_sum != NULL) {
		if (frame_sum[0] < 1) {
			LOGINFO("frameDataHandle：帧数无效...\n");
			return -1;
		} else if (frame_sum[0] == 1) {
			return -1;
		} else {
			return -1;
		}
	}

	LOGERROR("#################获取数据错误\n");
	return -1;

	/**
     * 初始化一个解析器
     * 第一个参数是数据头
     * 第二个参数是数据头长度
     * 第三个参数是数据尾指针
     * 第四个参数是数据尾大小
     * 第五个参数是一整帧数据的大小
     */
    DataParser *data_parser = parser_init(_data_header, sizeof(common_data_header), _data_footer,
    		sizeof(_data_footer), sizeof(data));
    // 将要解析的数据逐个取出，添加到解析器中
//    for(uint8 i = 0; i < sizeof(data); i++)
//    {
//        // 解析数据，返回 RESULT_TRUE 代表成功解析出一组数据
//        if(parser_put_data(data_parser, data[i]) == RESULT_TRUE)
//        {
//            LOGINFO("frameDataHandle：成功解析出一帧数据...\n");
//
//            /* 一位一位取出解析后的数据 */
//            LOGINFO("frameDataHandle：第一个数据是：0x%x\n", parser_get_data(data_parser, 0));
//            LOGINFO("frameDataHandle：第二个数据是：0x%x\n", parser_get_data(data_parser, 1));
//            LOGINFO("frameDataHandle：第三个数据是：0x%x\n\n\n", parser_get_data(data_parser, 2));
//        }
//    }

    // 当不再需要解析器时，应该把解析器释放掉，回收内存，避免造成内存泄漏
//    parser_release(data_parser);
}

//int main()
//{
//    uint8 i;
//    // 数据头
//    uint8 data_header[] = {0xAA, 0xAA, 0x04, 0x80, 0x02};
//    // 要解析的数据，测试用
//    uint8 data[] = {
//        0xAA, 0xAA, 0x04, 0x80, 0x02, 0x00, 0x02, 0x7B, 0xAA, 0xAA, 0x04, 0x80,
//        0x02, 0x00, 0x08, 0x75, 0xAA, 0xAA, 0x04, 0x80, 0x02, 0x00, 0x9B, 0xE2,
//        0xAA, 0xAA, 0x04, 0x80, 0x02, 0x00, 0xF6, 0x87, 0xAA, 0xAA, 0x04, 0x80,
//        0x02, 0x00, 0xEC, 0x91, 0xAA, 0xAA, 0x04, 0x80, 0x02, 0x01, 0x15, 0x67,
//        0xAA, 0xAA, 0x04, 0x80, 0x02, 0x01, 0x49, 0x33, 0xAA, 0xAA, 0x04, 0x80,
//        0x02, 0x00, 0xE7, 0x96, 0xAA, 0xAA, 0x04, 0x80, 0x02, 0x00, 0x68, 0x15,
//        0xAA, 0xAA, 0x04, 0x80, 0x02, 0x00, 0x3C, 0x41, 0xAA, 0xAA, 0x04, 0x80,
//        0x02, 0x00, 0x66, 0x17, 0xAA, 0xAA, 0x04, 0x80, 0x02, 0x00, 0xA5, 0xD8,
//        0xAA, 0xAA, 0x04, 0x80, 0x02, 0x01, 0x26, 0x56, 0xAA, 0xAA, 0x04, 0x80,
//        0x02, 0x01, 0x73, 0x09, 0xAA, 0xAA, 0x04, 0x80, 0x02, 0x01, 0x64, 0x18,
//        0xAA, 0xAA, 0x04, 0x80, 0x02, 0x01, 0x8B, 0xF1, 0xAA, 0xAA, 0x04, 0x80,
//        0x02, 0x01, 0xC6, 0xB6, 0xAA, 0xAA, 0x04, 0x80, 0x02, 0x01, 0x7B, 0x01,
//        0xAA, 0xAA, 0x04, 0x80, 0x02, 0x00, 0xCB, 0xB2, 0xAA, 0xAA, 0x04, 0x80,
//        0x02, 0x00, 0x2C, 0x51, 0xAA, 0xAA, 0x04, 0x80, 0x02, 0xFF, 0xE5, 0x99
//    };
//
//   uint8* reData;
//   getParserData(data, reData);
//
//    return 0;
//}

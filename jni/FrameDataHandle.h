/*
 * FrameDataHandle.h
 *
 *  Created on: 2018年4月25日
 *      Author: ning
 */

#ifndef FRAMEDATAHANDLE_H_
#define FRAMEDATAHANDLE_H_

#include "parser.h"
#include "common.h"
//using namespace frameDataHandle;

long getParserData(char* data, long data_len, char* reData);

uint8* getParserData(uint8 *_data_header, uint8 _header_size, uint8 *_data_footer, uint8 _foot_size,
		uint8* data, long data_len);
/* @_cmd_type: 命令指针
 * @_type_size: 命令大小
 * @_cmd_id:命令id指针
 * @_cmd_size: 命令id大小
 */
#endif /* FRAMEDATAHANDLE_H_ */

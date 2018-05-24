/*
 * parser.cpp
 *
 *  Created on: 2018年4月24日
 *      Author: ning
 */

#include <stdlib.h>

#include "parser.h"
#include "common.h"
#include "queue.h"
#include "CRC.h"
#include "debug.h"
#include <stdio.h>
/**
 * 解析出第一帧数据
 */
uint8* parser_before_init(uint8 *_data_header, uint8 _header_size, uint8 *_data_footer,
		uint8 _foot_size, uint8* _data){
	uint8* ack_data;
	DataParser *parser = (DataParser *)malloc(sizeof(DataParser));
	bool is_end = false;
    parser->resule_pointer = NULL;
    parser->data_header = _data_header;
    parser->header_size = _header_size;
    parser->data_footer = _data_footer;
    parser->footer_size = _foot_size;
    parser->result_size = _data[_header_size + frame_type_size + cmd_id_size];
    parser->parserResult = RESULT_FALSE;

    LOGINFO("frameDataHandle : sizeof(_data): %d\n", sizeof(_data)/sizeof(_data[0]));
	while (!is_end)
	{
	    if((_header_size+_foot_size) > sizeof(_data) || (_header_size+_foot_size) == (uint8)0 || sizeof(_data) < (uint8)9)
	    {
	    	LOGINFO("frameDataHandle : sizeof(_data): 0x%x\n", sizeof(_data)/sizeof(_data[0]));
	    	free(parser);
	    	return NULL;
	    }

	    LOGINFO("frameDataHandle : sizeof(_data): %d\n", sizeof(_data));
	    uint8 CRC_Check[] = {0};
	    uint8 i=0;
		if (_data[i] != parser->data_header[0]) {
			LOGINFO("frameDataHandle : ReadDataHeaderError/n");
			free(parser);
			return NULL;
			//Response(ReadDataHeaderError)
		}

		CRC_Check[0] = parser->frame_type[0] = _data[i+sizeof(parser->data_header)];
		if (!is_command_value(parser->frame_type)) {
			LOGINFO("frameDataHandle : ReadDataCMDError/n");
			free(parser);
			return NULL;
		}

		CRC_Check[sizeof(CRC_Check)] = parser->cmd_id[0] = _data[i + parser->header_size + frame_type_size];
		CRC_Check[sizeof(CRC_Check)] = parser->cmd_id[1] = _data[i + sizeof(parser->data_header) + frame_type_size + 1];
		CRC_Check[sizeof(CRC_Check)] = parser->data_len[0] = _data[i + to_data_size -1];
		parser->frame_no[0] = _data[i + to_data_size + parser->data_len[0]];
		parser->frame_sum[0] = _data[i + to_data_size + parser->data_len[0] + frame_no_size];
		parser->frame_crc[0] = _data[i + to_data_size + parser->data_len[0] + frame_no_size + frame_sum_size];


		for (uint8 j=0;j<parser->data_len[0];j++)
		{
			CRC_Check[sizeof(CRC_Check)+j] = ack_data[sizeof(ack_data)+j] = _data[parser->frame_no[0]*total_size + to_data_size +j];
		}
		CRC_Check[sizeof(CRC_Check)] = parser->frame_no[0];
		CRC_Check[sizeof(CRC_Check)] = parser->frame_sum[0];

		uint8_t ret = CRC_CalculateCRC8(CRC_Check, sizeof(CRC_Check));
		if (ret != parser->frame_crc[0]) {
			LOGINFO("frameDataHandle : CRC校验失败 CRC8 frame_crc: 0x%X  CRC: 0x%X\n", parser->frame_crc[0], ret);
			free(parser);
			return NULL;
		}
		LOGINFO("frameDataHandle : CRC校验成功 CRC: 0x%X/n", ret);
		memset(CRC_Check, 0, sizeof(CRC_Check));

		i = i + total_size;
		if ((parser->frame_sum[0] - parser->frame_no[0]) == 1) {
			is_end = true;
		}

	}

	LOGINFO("frameDataHandle :/n");
	for (uint8 i=0;i<sizeof(ack_data);i++) {
		LOGINFO("0x%x ",ack_data[i]);
		if ((i!=0) && (i%30 == 0)) {
			LOGINFO("/n");//够一定个数就换行
		}
	}
	free(parser);
	return ack_data;
}


/**
 * 初始化一个解析器
 *
 * @_data_header: 数据头指针
 * @_header_size: 数据头大小
 * @_data_footer: 数据尾指针
 * @_foot_size: 数据尾大小
 * @_data_frame_size: 一帧完整数据的大小
 *
 * @return: 解析器
 */
DataParser *parser_init(uint8 *_data_header, uint8 _header_size, uint8 *_data_footer, uint8 _foot_size, uint8 _data_frame_size)
{
    if((_header_size+_foot_size) > _data_frame_size || (_header_size+_foot_size) == 0)
        return NULL;

    DataParser *parser = (DataParser *)malloc(sizeof(DataParser));
    parser->parser_queue = init_queue(_data_frame_size);
    parser->resule_pointer = NULL;
    parser->data_header = _data_header;
    parser->header_size = _header_size;
    parser->data_footer = _data_footer;
    parser->footer_size = _foot_size;
    parser->result_size = _data_frame_size - parser->header_size - parser->footer_size;
    parser->parserResult = RESULT_FALSE;

    while(_data_frame_size-- > 0)
    {
//        en_queue(parser->parser_queue, 0);
    }

    return parser;
}

/**
 * 将数据添加到解析器中进行解析
 *
 * @_parser: 解析器
 * @_data: 要解析的数据
 *
 * @return: 当前解析结果，返回 RESULT_TRUE 代表成功解析出一帧数据
 */
//ParserResult parser_put_data(DataParser *_parser, uint8 _data)
//{
//    uint8 i;
//    Node *node;
//
//    if(_parser == NULL)
//        return RESULT_FALSE;
//
//    en_queue(_parser->parser_queue, _data);
//
//    /* 校验数据尾 */
//    node = _parser->parser_queue->back;
//    for(i = _parser->footer_size; i > 0; i--)
//    {
//        if(node->data != _parser->data_footer[i-1])
//            goto DATA_FRAME_FALSE;
//        node = node->pre_node;
//    }
//
//    /* 校验数据头 */
//    node = _parser->parser_queue->front;
//    for(i = 0; i < _parser->header_size; i++)
//    {
//        if(node->data != _parser->data_header[i])
//            goto DATA_FRAME_FALSE;
//        node = node->next_node;
//    }
//
//    if(_parser->resule_pointer == NULL && _parser->result_size > 0)
//        _parser->resule_pointer = node;
//    if(_parser->parserResult != RESULT_TRUE)
//        _parser->parserResult = RESULT_TRUE;
//    return _parser->parserResult;
//
//DATA_FRAME_FALSE:
//    if(_parser->resule_pointer != NULL)
//        _parser->resule_pointer = NULL;
//    if(_parser->parserResult != RESULT_FALSE)
//        _parser->parserResult = RESULT_FALSE;
//    return _parser->parserResult;
//
//}
//
///**
// * 解析成功后从解析器中取出解析结果
// *
// * @_parser: 解析器
// * @_index: 解析结果集合中的第 _index 个数据
// *
// * @return: 获取解析成功的数据，返回 -1 代表数据获取失败
// */
//int parser_get_data(DataParser *_parser, uint8 _index)
//{
//    Node *node;
//    if(_parser == NULL
//    || _parser->parserResult != RESULT_TRUE
//    || _index >= _parser->result_size
//    || _parser->resule_pointer == NULL)
//        return -1;
//    node = _parser->resule_pointer;
//    while(_index > 0)
//    {
//        node = node->next_node;
//        _index--;
//    }
//    return node->data;
//}
//
///**
// * 重置解析器
// *
// * @_parser: 解析器
// */
//void parser_reset(DataParser *_parser)
//{
//    uint8 _data_frame_size;
//
//    if(_parser == NULL)
//        return;
//
//    _data_frame_size = _parser->parser_queue->size;
//    while(_data_frame_size-- > 0)
//    {
//        en_queue(_parser->parser_queue, 0);
//    }
//    _parser->resule_pointer = NULL;
//    _parser->parserResult = RESULT_FALSE;
//}
//
///**
// * 释放解析器
// *
// * @_parser: 解析器
// */
//void parser_release(DataParser *_parser)
//{
//    if(_parser == NULL)
//        return;
//    release_queue(_parser->parser_queue);
//    free(_parser);
//    _parser = NULL;
//}
/**
 * 帧数据中检查命令是否有效
 * @_command: 命令
 */
bool is_command_value(uint8 *_command)
{
	LOGINFO("framedatahandle:命令为:%x\n", _command[0]);
	if ((_command[0] == 0x00) || (_command[0] == 0x01) || (_command[0] == 0x02))
	{
		return true;
	}
	return false;
}


/*
 * parser.h
 *
 *  Created on: 2018年4月24日
 *      Author: ning
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <queue.h>

typedef enum
{
    RESULT_FALSE,
    RESULT_TRUE
} ParserResult;

/* 解析器结构 */
typedef struct DataParser
{
    Queue *parser_queue;            // 数据解析队列
    Node *resule_pointer;           // 解析结果数据指针
    uint8 *data_header;             // 数据校验头指针
    uint8 header_size;              // 数据校验头大小
    uint8 *data_footer;             // 数据校验尾指针
    uint8 footer_size;              // 数据校验尾大小
    uint8 result_size;              // 解析数据大小
    ParserResult parserResult;      // 解析结果
    uint8 *frame_type;              // 命令类型指针
    uint8 *cmd_id;                  // cmd命令ID指针
    uint8 *data_len;                // 数据长度指针
    uint8 *frame_no;                // 该帧的号码指针
    uint8 *frame_sum;               // 数据帧的总数指针
    uint8 *frame_crc;               // 数据crc的指针
} DataParser;

/* 初始化一个解析器 */
uint8 *parser_before_init(uint8 *_data_header, uint8 _header_size, uint8 *_data_footer,
		uint8 _foot_size, uint8* _data);

/* 初始化一个解析器 */
DataParser *parser_init(uint8 *_data_header, uint8 _header_size, uint8 *_data_footer, uint8 _foot_size, uint8 _data_frame_size);
/* 将数据添加到解析器中进行解析 */
ParserResult parser_put_data(DataParser *_parser, uint8 _data);
/* 解析成功后从解析器中取出解析结果 */
int parser_get_data(DataParser *_parser, uint8 _index);
/* 重置解析器 */
void parser_reset(DataParser *_parser);
/* 释放解析器 */
void parser_release(DataParser *_parser);
/*命令是否有效*/
bool is_command_value(uint8 *command);
#endif /* UTILS_PARSER_H_ */

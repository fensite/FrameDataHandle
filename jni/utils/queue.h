/*
 * queue.h
 *
 *  Created on: 2018年4月24日
 *      Author: ning
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "common.h"

#ifndef NULL
#define NULL    ((void *)0)
#endif

//typedef unsigned char uint8;

/* 队列节点 */
typedef struct Node
{
    uint8 data;
    struct Node *pre_node;
    struct Node *next_node;
} Node;



/* 队列结构 */
typedef struct Queue
{
    uint8 capacity;     // 队列总容量
    uint8 size;         // 当前队列大小
    Node *front;        // 队列头节点
    Node *back;         // 队列尾节点
} Queue;

/* 初始化一个队列 */
Queue *init_queue(uint8 _capacity);
/* 数据入队 */
uint8 en_queue(Queue *_queue, uint8 _data);
/* 数据出队 */
uint8 de_queue(Queue *_queue);
/* 清空队列 */
void clear_queue(Queue *_queue);
/* 释放队列 */
void release_queue(Queue *_queue);

#endif /* UTILS_QUEUE_H_ */

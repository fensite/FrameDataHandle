/*
 * commondFrame.cpp
 *
 *  Created on: 2018年5月3日
 *      Author: ning
 */

#include <commondFrame.h>
#include "debug.h"

commondFrame::commondFrame() {
	// TODO Auto-generated constructor stub

}

commondFrame::~commondFrame() {
	// TODO Auto-generated destructor stub
}

void commondFrame::setData(uint8 data)
{

}
uint8 commondFrame::parseFrameData(uint* frameData, long length)
{
	LOGINFO("data len is %d" ,length);
	string inputData;
	for (int i=0;i<length;i++) {

	}
}
uint8 commondFrame::isFrameValid(uint* frameData, long len)
{
	if (mFrameHead != FRAME_HEAD_CODE) {
		return UNKNOW_ERROR;
	} else if (mEndCode != FRAME_END_CODE) {
		return UNKNOW_ERROR;
	} else if (mFrameNum >= mFrameSum) {
		return UNKNOW_ERROR;
	}
	return true;
}

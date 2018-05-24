/*
 * commondFrame.h
 *
 *  Created on: 2018年5月3日
 *      Author: ning
 */

#ifndef UTILS_COMMONDFRAME_H_
#define UTILS_COMMONDFRAME_H_

#include "common.h"
#include <string>
using namespace std;

class commondFrame {

public:
	commondFrame();
	virtual ~commondFrame();

	uint8 getFrameHead(){return mFrameHead;};
	uint8 getFrameLen(){return mFrameLen;};
	uint8 getFrameFuctionCode(){return mFrameFuctionCode;};
	uint8 getFrameCommondType(){return mFrameCommondType;};
	uint8 getFrameSum(){return mFrameSum;};
	uint8 getFrameNum(){return mFrameNum;};
	uint8 getErrorCode(){return mErrorCode;};
	uint8 getCheckCode(){return mCheckCode;};
	uint8 getEndCode(){return mEndCode;};
	string getData(){return mJsonData;};


	void setFrameFuctionCode(uint8 frameFunctionCode){mFrameFuctionCode = frameFunctionCode;};
	void setFrameCommondType(uint8 frameCommondType){mFrameCommondType = frameCommondType;};

	void setErrorCode(uint8 errorCode){mErrorCode = errorCode;};
	void setData(uint8 data);
	uint8 parseFrameData(uint* frameData, long length);
	uint8 getFrameData();

	static uint8 FRAME_HEAD_CODE = 0xFB; //起始标志，固定值
	static uint8 FRAME_END_CODE = 0xFC; //结束标志，固定值

	static uint8 FRAME_FUNCTION_MAC = 0x01; //功能字MAC地址
	static uint8 FRAME_FUNCTION_WIFI = 0x02; //功能字wifi配置
	static uint8 FRAME_FUNCTION_INSTALLED_APP_LIST = 0x03; //功能字已安装应用列表
	static uint8 FRAME_FUNCTION_PAGE = 0x04; //功能字页面列表
	static uint8 FRAME_FUNCTION_DATA_OF_SPEECH = 0x05; //功能字语音解析数据
	static uint8 FRAME_FUNCTION_VOLUME_SYN = 0x06; //功能字音量同步

	static uint8 NO_ERROR = 0x00; //成功
	static uint8 CHECK_ERROR = 0x01; //校验错误
	static uint8 TIME_OUT = 0x02; //发送超时，在规定时间内未收到完整的报文
	static uint8 UNKNOW_ERROR = 0x03; //未知的错误

private:
	uint8 isFrameValid(uint* frameData, long len);

	void setFrameHead(uint8 frameHead){mFrameHead = frameHead;};
	void setFrameLen(uint8 frameLen){mFrameLen = frameLen;};
	void setFrameSum(uint8 frameSum){mFrameSum = frameSum;};
	void setFrameNum(uint8 frameNum){mFrameNum = frameNum;};
	void setCheckCode(uint8 checkCode){mCheckCode = checkCode;};
	void setEndCode(uint8 endCode){mEndCode = endCode;};

	uint8 mFrameHead;
	uint8 mFrameLen;
	uint8 mFrameFuctionCode;
	uint8 mFrameCommondType;
	uint8 mFrameSum;
	uint8 mFrameNum;
	uint8 mErrorCode;
	string mJsonData;
	uint8 mCheckCode;
	uint8 mEndCode;

};

#endif /* UTILS_COMMONDFRAME_H_ */

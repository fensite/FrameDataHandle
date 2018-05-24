package com.zkn.utils;

import android.util.Log;

import java.nio.charset.Charset;

/**
 * Created by zhaikangning on 2018/4/30.
 */

public class FrameDataHandlerTools {
    private final String TAG = "SerialFrameDataParser";

    public final static int   FRAME_HEADER=0xFB;
    public final static int   FRAME_END_CODE=0xFC;
    public final static byte  FRAME_TYPE_CMD=0x0;  //  0000 0000
    public final static byte  FRAME_TYPE_ACK=0x1;  //  0001 0000
    public final static int   FRAME_MIN=10;
    public final static int   FRAME_MAX=256*1024;
    // 功能字
    public final static byte  FRAME_FUNCTION_MAC_ADDR=0x01; //功能字：mac地址
    public final static byte  FRAME_FUNCTION_WIFI_CONFIG=0x02; //功能字：wifi配置
    public final static byte  FRAME_FUNCTION_INSTALLED_APP_LIST=0x03; //功能字：已安装应用列表
    public final static byte  FRAME_FUNCTION_PAGE_LIST=0x04; //功能字：页面列表
    public final static byte  FRAME_FUNCTION_AI_PARSE_DATA=0x05; //功能字：语音解析数据
    public final static byte  FRAME_FUNCTION_SYN_VOLUME =0x06; //功能字：音量同步

    private byte mFrameHead;
    private int  mFrameLen;
    private int  mFrameDataLen;
    private byte mFrameFunctionCode;
    private byte mFrameType;
    private byte mFrameSum;
    private byte mFrameNo;
    private byte mFrameErrorCode;
    private String mFrameValueData;
    private byte mFrameCheckCode;
    private byte mFrameEndCode;
    private byte[] mBuildFrameData;

//    private

    public byte getFrameLen() {return (byte)mFrameLen;}
    public byte getFrameFunctionCode() {return mFrameFunctionCode;}
    public byte getFrameType() {return mFrameType;}
    public byte getFrameSum() {return mFrameSum;}
    public byte getFrameNo() {return mFrameNo;}
    public byte getFrameErrorCode() {return mFrameErrorCode;}
    public byte getmFrameCheckCode() {return mFrameCheckCode;}
    public String getFrameValueData() {return mFrameValueData;}

    public byte[] buildFrameData(String frameValueData, byte frameType, byte functionCode, byte errorCode) {
        if (frameValueData.isEmpty()) {
            Log.i(TAG, "===帧数据为空");
        } else {
            Log.i(TAG, "===帧数据 : " + frameValueData);
        }
        Log.i(TAG, "===帧类型 : 0x" + byte2HexString(frameType));
        Log.i(TAG, "===功能字 : 0x" + byte2HexString(functionCode));
        Log.i(TAG, "===功能字说明：0x01=mac地址|0x02=wifi配置|0x03=已安装应用列表|0x04=页面列表|0x05=语音解析数据|0x06=音量同步");
        Log.i(TAG, "===错误码 : 0x" + byte2HexString(errorCode));
        Log.i(TAG, "===错误码说明：0x00=正常|0x01=校验错误|0x02=发送超时，在规定时间(未确定，暂预留)内未收到完整的报文数据|0x03=未知功能字");

        byte[]  frameDataUTF8 = frameValueData.getBytes(Charset.forName("UTF-8"));
        byte[]  frameDataGBK = frameValueData.getBytes(Charset.forName("GBK"));
        int totalDataLen = frameDataUTF8.length;  //所有帧的数据长度之和

        Log.i(TAG,"===build frameValueData length(" + frameValueData.length() + ")" + " || frameDataUTF8 length(" + totalDataLen + ")");
        Log.i(TAG,"===build frameDataGBK length(" + frameDataGBK.length + ")" );

        int frameSum = 1; //帧数默认为1
        if (frameDataUTF8.length>(1024-10)) {
            if (frameDataUTF8.length%(1024-10) != 0) {
                frameSum = frameDataUTF8.length/(1024-10) + 1;
            } else {
                frameSum = frameDataUTF8.length/(1024 - 10);
            }
        }
        Log.i(TAG,"===build 帧数据共" + frameSum + "帧");

        mBuildFrameData = new byte[10*frameSum + totalDataLen];  //设置生成数组长度
        int singleDataLen = 0; //单帧的数据长度，默认为0
        for (int i=0;i<frameSum;i++) { //i相当于上一帧序的值，只有1帧时，i=0   ; 每次循环都是对一帧数据的操作
            Log.i(TAG,"===这是第 " + (i+1) + " 帧");
            mBuildFrameData[0 + i*1024] = (byte)FRAME_HEADER;
            Log.i(TAG, "===帧头 : 0x" + byte2HexString(mBuildFrameData[0 + i*1024]));

            if(i+1 == frameSum) { //如果这帧数据帧序和总帧数相等则执行该代码块
                singleDataLen = totalDataLen - i*(1024-10);
                mFrameDataLen = singleDataLen+10;
                mBuildFrameData[2 + i*1024] = (byte) ((mFrameDataLen&0xFF00)>>8);     //get Hight of 2Byte Off len
                mBuildFrameData[1 + i*1024] = (byte) (mFrameDataLen&0x00FF);          //get Low of 2Byte Off len
            } else {
                singleDataLen = (1024-10); //总数据长度减去前几帧数据长度之和
                mFrameDataLen = singleDataLen+10;
                mBuildFrameData[2 + i*1024] = (byte) ((mFrameDataLen&0xFF00)>>8);   //get Hight of 2Byte Off len
                mBuildFrameData[1 + i*1024] = (byte) (mFrameDataLen&0x00FF);        //get Low of 2Byte Off len
            }
            Log.i(TAG, "===总长度高8位 : 0x" + byte2HexString(mBuildFrameData[2 + i*1024]));
            Log.i(TAG, "===总长度低8位 : 0x" + byte2HexString(mBuildFrameData[1 + i*1024]));

            mBuildFrameData[3 + i*1024] = functionCode;
            mBuildFrameData[4 + i*1024] = frameType;
            mBuildFrameData[5 + i*1024] = (byte)frameSum;
            mBuildFrameData[6 + i*1024] = (byte) (i+1);
            mBuildFrameData[7 + i*1024] = errorCode;

            for (int j=0;j<singleDataLen;j++) {
                mBuildFrameData[8+j+i*1024] = frameDataUTF8[j+i*(1024-10)];
            }

            byte[] sumIA = new byte[mFrameDataLen];
            for (int k=0;k<mFrameDataLen;k++) {
                sumIA[k] = mBuildFrameData[k+i*1024];
            }
            Log.i(TAG, "===sumAI[] = " + bytes2HexString(sumIA));
            Log.i(TAG, "===sumAI = " + byte2HexString(calc_checksum(sumIA)));

            byte sum = checkSum(mBuildFrameData, i*1024, (singleDataLen + 8));
            byte converseSum = (byte)~sum;
            Log.i(TAG, "===求和 : 0x" + byte2HexString(sum));
            Log.i(TAG, "===求和反码 : 0x" + byte2HexString(converseSum));
            mBuildFrameData[8+singleDataLen + i*1024] = sum;
            mBuildFrameData[9+singleDataLen + i*1024] = (byte)FRAME_END_CODE;
        }
        Log.i(TAG, "===生成帧总长度 : " + mBuildFrameData.length);

        /**
         * 测试使用，使用十六进制打印所有数据
         */
        String buildData2Str = bytes2HexString(mBuildFrameData);
        Log.i(TAG, "mBuildFrameData is " + buildData2Str);

        return mBuildFrameData;
    }


    public String dataParser(byte[] frameData, int dataSize) {
        if (frameData.length < FRAME_MIN || frameData.length >= FRAME_MAX) {
            Log.e(TAG, "===ERROR: frameData.length is : " + frameData.length);

            return ""; //
        }

        mFrameNo = 0x00;
        mFrameSum = 0x01; //初始化为了进入while循环
        int totalFrameLen = 0;

        byte[] reFrameData = new byte[256*1024];
        while (mFrameNo < mFrameSum) {
            mFrameHead = frameData[0 + totalFrameLen];
            Log.i(TAG, "===frameHead is " + byte2HexString(mFrameHead));
            if (mFrameHead != (byte)FRAME_HEADER) {
                Log.e(TAG,"FrameData headCode Error,code:" + mFrameEndCode);
                return "";
            }

            mFrameLen=frameData[2 +totalFrameLen]&0xFF;
            mFrameLen=mFrameLen<<8;//Set H
            mFrameLen=mFrameLen|(frameData[1 + totalFrameLen]&0xFF); //Set L

            Log.i(TAG,"===mFrameLen is : " + mFrameLen + "  ||  高八位 ：" + byte2HexString(frameData[2]) + "|低八位 : " + byte2HexString(frameData[1]));
            Log.i(TAG,"===单帧总长度：" + mFrameLen);
            if (mFrameLen<0 || mFrameLen>1024 || (mFrameLen != dataSize)) {
                Log.e(TAG, "===parser Datasize is " + dataSize);
                Log.e(TAG,"FrameData len Error!");
                return "";
            }

            mFrameFunctionCode = frameData[3 + totalFrameLen];
            mFrameType = frameData[4 + totalFrameLen];
            mFrameSum = frameData[5 + totalFrameLen];
            byte thisFrameNo = frameData[6 + totalFrameLen];
            if (thisFrameNo > mFrameSum) {
                Log.e(TAG,"===当前帧序" + byte2HexString(mFrameNo) + "大于总帧数" + byte2HexString(mFrameSum) + "，数据有误！");
                return "";
            }

            mFrameErrorCode = frameData[7 + totalFrameLen];
            mFrameCheckCode = frameData[totalFrameLen + mFrameLen -2];
            mFrameEndCode = frameData[totalFrameLen + mFrameLen - 1];
            if (mFrameEndCode != (byte)FRAME_END_CODE) {
                Log.e(TAG,"FrameData endCode Error,code:" + byte2HexString(mFrameEndCode));
                return "";
            }

            byte[] pintByte = new byte[mFrameLen - 10];
            for (int i=0;i<(mFrameLen-10);i++) {
                pintByte[i] = reFrameData[i + totalFrameLen - (thisFrameNo-1)*10] = frameData[8+i+totalFrameLen];
            }

            /**
             * 测试使用，使用十六进制打印所有数据
             */
            String buildData2Str = bytes2HexString(pintByte);
            Log.i(TAG, "mBuildFrameData is " + buildData2Str);

            // 判断下一个帧序是否有效
            byte nextFrameNo = frameData[totalFrameLen + 6];
            if (((int)(nextFrameNo)-(int)(mFrameNo)) !=1) {
                Log.e(TAG, "===thisFrameNo" + byte2HexString(mFrameNo));
                Log.e(TAG, "===nextFrameNo" + byte2HexString(nextFrameNo) +" ERROR！");
                return "";
            }

            //checkSum check
            byte calCheckSum=checkSum(frameData, totalFrameLen,totalFrameLen + mFrameLen - 2);
            Log.i(TAG, "===mFrameCheckCode:" + byte2HexString(mFrameCheckCode) +";Check sum is:" + byte2HexString(calCheckSum));
            if(mFrameCheckCode != calCheckSum) {
                Log.e(TAG,"===和校验错误，ERROR");
//                return "";
            }

            mFrameNo = nextFrameNo;
            totalFrameLen = totalFrameLen+mFrameLen;
        }

        String paserStr = new String(reFrameData, 0, reFrameData.length, Charset.forName("UTF-8")).trim();
        Log.i(TAG,"===paseredStr is" + paserStr);
        return paserStr;
    }

    /*
     * 字节转16进制字符串
    */
    public static String byte2HexString(byte b) {
        String r = "";

        String hex = Integer.toHexString(b & 0xFF);
        if (hex.length() == 1) {
            hex = '0' + hex;
        }
        r += hex.toUpperCase();
        return r;
    }

    /*
  * 字节数组转16进制字符串
 */
    public static String bytes2HexString(byte[] b) {
        String r = "";

        for (int i = 0; i < b.length; i++) {
            String hex = Integer.toHexString(b[i] & 0xFF);
            if (hex.length() == 1) {
                hex = '0' + hex;
            }
            hex =  " 0x" + hex;
            r += hex.toUpperCase();
        }

        return r;
    }

    public static byte checkSum(byte[] src,int srcPos,int len)
    {
        if((src.length<srcPos)||(src==null)) {return 0x0;}
        final int MAX=(srcPos+len)>src.length?src.length:srcPos+len;
        int sum=0;
        for (int i=srcPos;i<MAX;i++){
            sum+=(int)(src[i]&0xff);
        }
        byte checkSum=(byte)(sum%256);
        checkSum=(byte) ((checkSum^0xff)+1);
        return checkSum;
    }

    private byte calc_checksum(byte[] byteArray) {
        int i;
        byte checksum = 0;
        for(i = 0; i < byteArray.length-2; i++) {
            checksum += byteArray[i];
        }
        checksum = (byte)((0 - checksum) & 0xFF);
        return checksum;
    }
}

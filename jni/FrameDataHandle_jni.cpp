#include <jni.h>

#include "FrameDataHandle.h"
#include "debug.h"
#include <stdio.h>
#define TRANSFER_DATA "tv/newtv/framedatahandle/TransferData"

#ifdef __cplusplus
extern "C" {
#endif

JavaVM* gVM = NULL;

JNIEnv* GetEnv()
{
   JNIEnv* env = NULL;
   if (gVM) {
      jint ret = gVM->GetEnv((void**) &env, JNI_VERSION_1_6);
      if (ret != JNI_OK) {
         jint status = gVM->AttachCurrentThread(&env, NULL);
         if (status < 0) {
            LOGINFO("framedatahandle: failed to attach current thread\n");
            env = NULL;
         }
      }
   }
   return env;
}

void DetachEnv()
{
   gVM->DetachCurrentThread();
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    return JNI_VERSION_1_6;
}

static char* ConvertJByteaArrayToChars(JNIEnv *env, jbyteArray bytearray)
{
	char *chars = NULL;
	jbyte *bytes;
	bytes = env->GetByteArrayElements(bytearray, 0);
	int chars_len = env->GetArrayLength(bytearray);
	chars = new char[chars_len + 1];
	memset(chars, 0, chars_len + 1);
	memcpy(chars, bytes, chars_len);
	chars[chars_len] = 0;

	env->ReleaseByteArrayElements(bytearray, bytes, 0);

	return chars;
}

JNIEXPORT jlong JNICALL Java_tv_newtv_framedatahandle_FrameDataHandle_getParserData
(JNIEnv *env, jobject thiz, jbyteArray data, jlong data_len,jbyteArray responeData)
{
	LOGINFO("FrameDataHandle: 进入jni\n");
	char *_data = ConvertJByteaArrayToChars(env, data);
	char *_responseData = ConvertJByteaArrayToChars(env, data);

	return getParserData(_data, data_len ,_responseData);
//	return true;
}

#ifdef __cplusplus
}
#endif

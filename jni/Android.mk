LOCAL_PATH := $(call my-dir)

OUTPUT_TYPE=ANDROID_JAR
define all-files-under
$(patsubst ./%,%, \
  $(shell cd $(LOCAL_PATH) ; \
          find $(1) -name "$(2)" -and -not -name ".*") \
 )
endef

define all-cpp-files-under
$(call all-files-under,$(1),*.cpp)
endef

define all-cc-files-under
$(call all-files-under,$(1),*.cc)
endef

define all-c-files-under
$(call all-files-under,$(1),*.c)
endef

define all-S-files-under
$(call all-files-under,$(1),*.S)
endef

define set-git-version
$(shell $(LOCAL_PATH)/set_version.sh)
endef

include $(CLEAR_VARS)

LOCAL_MODULE := FrameDataHandle

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/utils

LOCAL_SRC_FILES := $(call all-cpp-files-under, utils) \
					FrameDataHandle_jni.cpp \
					FrameDataHandle.cpp

LOCAL_LDLIBS     += -fuse-ld=bfd -rdynamic -llog -lz

$(call set-git-version)

ifeq ($(OUTPUT_TYPE), ANDROID_JAR)
	LOCAL_MODULE_FILENAME := libFrameDataHandle
	LOCAL_CPPFLAGS += -DPURE_SDK
	
	include $(BUILD_SHARED_LIBRARY)
endif

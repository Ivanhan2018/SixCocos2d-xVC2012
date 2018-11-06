LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

##############
# Variable   #
##############
LOCAL_MODULE := l9threegong_shared

LOCAL_MODULE_FILENAME := libl9threegong

##############
# Source     #
##############
LOCAL_SRC_FILES := l9threegong/main.cpp
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)

##############
# Dependency #
##############
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/*.cpp)
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/Base_Interface/*.cpp)
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/Game_Interface/*.cpp)
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/JNI_Interface/*.cpp)
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/Shared_Interface/*.cpp)
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/Net_Interface/*.cpp)
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/UI_Interface/*.cpp)
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/tinyxml/*.cpp)
LOCAL_SRC_FILES := $(LOCAL_SRC_FILES:$(LOCAL_PATH)/%=%)

##############
# Headers    #
##############
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../CocosDenshion
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../extensions

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework/Base_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework/Game_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework/JNI_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework/Shared_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework/Net_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework/UI_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework/tinyxml

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../GoodFrame/PUBLIC_H
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../GoodFrame/common
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../GoodFrame/APP_HEAD
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../GoodFrame/gameapp/SanGong/GameMsg

##############
# Flags      #
##############
LOCAL_CFLAGS += $(TOOL_CFLAGS) -fpermissive
LOCAL_CFLAGS += -Wdeprecated-declarations
LOCAL_CFLAGS += -std=c++11
#LOCAL_CFLAGS += -DTIXML_USE_STL

##############
# Library    #
##############
LOCAL_WHOLE_STATIC_LIBRARIES := cocos_testcpp_common
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
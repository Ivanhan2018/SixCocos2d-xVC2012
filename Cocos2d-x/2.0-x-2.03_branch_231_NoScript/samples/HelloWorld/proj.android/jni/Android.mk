LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := helloworld_shared

LOCAL_MODULE_FILENAME := libhelloworld

LOCAL_SRC_FILES := helloworld/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,E:/2.0-x-2.03)
$(call import-add-path,E:/2.0-x-2.03/cocos2dx/platform/third_party/android/prebuilt)
$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
#$(call import-module,extensions)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := l9fish_shared

LOCAL_MODULE_FILENAME := libl9fish

LOCAL_SRC_FILES := l9fish/main.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/BulletAndNetMgr.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/CCActionEx.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/Curve.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/FishManage.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/Gold.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/Ship.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_ClientLogic.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_ClientLogin.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_ClientRoom.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_ConsoleGM.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_LoginPanel.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_MatchEnd.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_MatchList.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_PlayerMgr.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_PopWndBuyBullet.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_PopWndRank.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_PopWndSellFish.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_PopWndSetting.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_RippleGrid3D.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_RoomList.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_RoomMgr.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_SceneGame.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_SceneGate.cpp
LOCAL_SRC_FILES += ../../Classes/SIX_Classes/SIX_World.cpp

##############
# Dependency #
##############
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/*.cpp)
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/Base_Interface/*.cpp)
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/Shared_Interface/*.cpp)
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/Net_Interface/*.cpp)
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/UI_Interface/*.cpp)
LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/../../../../Six_Framework/tinyxml/*.cpp)
LOCAL_SRC_FILES := $(LOCAL_SRC_FILES:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/SIX_Classes

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../CocosDenshion
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../extensions
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework/Base_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework/Shared_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework/Net_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework/UI_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Six_Framework/tinyxml

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../GoodFrame/PUBLIC_H
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../GoodFrame/common
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../GoodFrame/APP_HEAD
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../GoodFrame/gameapp/fish/gamemsg

LOCAL_CFLAGS += $(TOOL_CFLAGS) -fpermissive
LOCAL_CFLAGS += -Wdeprecated-declarations
LOCAL_CFLAGS += -std=c++11
#LOCAL_CFLAGS += -DTIXML_USE_STL

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
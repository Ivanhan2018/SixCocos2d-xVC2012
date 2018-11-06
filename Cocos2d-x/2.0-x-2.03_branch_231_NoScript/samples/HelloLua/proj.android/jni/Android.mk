LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellolua_shared

LOCAL_MODULE_FILENAME := libhellolua

LOCAL_SRC_FILES := hellolua/main.cpp
LOCAL_SRC_FILES += ../../Classes/AppDelegate.cpp
LOCAL_SRC_FILES += ../../../../scripting/lua/cocos2dx_support/CCLuaEngine.cpp
LOCAL_SRC_FILES += ../../../../scripting/lua/cocos2dx_support/Cocos2dxLuaLoader.cpp 
LOCAL_SRC_FILES += ../../../../scripting/lua/cocos2dx_support/LuaCocos2d.cpp
LOCAL_SRC_FILES += ../../../../scripting/lua/cocos2dx_support/tolua_fix.c

LOCAL_SRC_FILES += ../../../../Utility/tinyxml/tinystr.cpp
LOCAL_SRC_FILES += ../../../../Utility/tinyxml/tinyxml.cpp
LOCAL_SRC_FILES += ../../../../Utility/tinyxml/tinyxmlerror.cpp
LOCAL_SRC_FILES += ../../../../Utility/tinyxml/tinyxmlparser.cpp

LOCAL_SRC_FILES += ../../../../Utility/Net_Interface/SIX_Http.cpp
LOCAL_SRC_FILES += ../../../../Utility/Net_Interface/SIX_PackageMgr.cpp
LOCAL_SRC_FILES += ../../../../Utility/Net_Interface/SIX_Proxy.cpp
LOCAL_SRC_FILES += ../../../../Utility/Net_Interface/SIX_Socket.cpp
LOCAL_SRC_FILES += ../../../../Utility/Net_Interface/SIX_SocketClient.cpp
LOCAL_SRC_FILES += ../../../../Utility/Net_Interface/SIX_Thread.cpp

LOCAL_SRC_FILES += ../../../../Utility/UI_Interface/SIX_EditBox.cpp
LOCAL_SRC_FILES += ../../../../Utility/UI_Interface/SIX_ListView.cpp
LOCAL_SRC_FILES += ../../../../Utility/UI_Interface/SIX_ListViewCell.cpp
LOCAL_SRC_FILES += ../../../../Utility/UI_Interface/SIX_ScrollBar.cpp
LOCAL_SRC_FILES += ../../../../Utility/UI_Interface/SIX_UILayer.cpp

LOCAL_SRC_FILES += ../../../../Utility/CCActionEx.cpp
LOCAL_SRC_FILES += ../../../../Utility/SIX_GlobalMgr.cpp
LOCAL_SRC_FILES += ../../../../Utility/SIX_MusicMgr.cpp
LOCAL_SRC_FILES += ../../../../Utility/SIX_SceneMgr.cpp
LOCAL_SRC_FILES += ../../../../Utility/SIX_UIMgr.cpp
LOCAL_SRC_FILES += ../../../../Utility/SIX_UIScene.cpp
LOCAL_SRC_FILES += ../../../../Utility/SIX_Utility.cpp
LOCAL_SRC_FILES += ../../../../Utility/SIX_XMLParser.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../CocosDenshion
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../extensions
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Utility
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Utility/tinyxml
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Utility/Lua_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Utility/SIX_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Utility/UI_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../Utility/Net_Interface
               
LOCAL_CFLAGS += -fpermissive
LOCAL_CFLAGS += -Wdeprecated-declarations
LOCAL_CFLAGS += -DTIXML_USE_STL

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_libxml2_static

LOCAL_WHOLE_STATIC_LIBRARIES += cocos_libiconv_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,scripting/lua/proj.android/jni)

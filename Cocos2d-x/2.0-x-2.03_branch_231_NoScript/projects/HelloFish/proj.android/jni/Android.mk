LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := helloworld_shared

LOCAL_MODULE_FILENAME := libhelloworld

LOCAL_SRC_FILES := helloworld/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/SIX_Classes/BulletAndNetMgr.cpp \
                   ../../Classes/SIX_Classes/CCActionEx.cpp \
                   ../../Classes/SIX_Classes/Curve.cpp \
                   ../../Classes/SIX_Classes/FishManage.cpp \
                    ../../Classes/SIX_Classes/Gold.cpp \
                    ../../Classes/SIX_Classes/Ship.cpp \
                   ../../Classes/SIX_Classes/SIX_ClientLogic.cpp \
                   ../../Classes/SIX_Classes/SIX_ClientLogin.cpp \
                    ../../Classes/SIX_Classes/SIX_ClientRoom.cpp \
                    ../../Classes/SIX_Classes/SIX_ConsoleGM.cpp \
                   ../../Classes/SIX_Classes/SIX_LoginPanel.cpp \
                   ../../Classes/SIX_Classes/SIX_LoginPanelSG.cpp \
                    ../../Classes/SIX_Classes/SIX_MatchEnd.cpp \
                    ../../Classes/SIX_Classes/SIX_MatchList.cpp \
                   ../../Classes/SIX_Classes/SIX_PlayerMgr.cpp \
                    ../../Classes/SIX_Classes/SIX_PopWndBuyBullet.cpp \
                   ../../Classes/SIX_Classes/SIX_PopWndRank.cpp \
                    ../../Classes/SIX_Classes/SIX_PopWndSellFish.cpp \
                    ../../Classes/SIX_Classes/SIX_PopWndSetting.cpp \
                   ../../Classes/SIX_Classes/SIX_RippleGrid3D.cpp \
                    ../../Classes/SIX_Classes/SIX_RoomList.cpp \
                     ../../Classes/SIX_Classes/SIX_RoomMgr.cpp \
                    ../../Classes/SIX_Classes/SIX_SceneGame.cpp \
                   ../../Classes/SIX_Classes/SIX_SceneGate.cpp \
                    ../../Classes/SIX_Classes/SIX_World.cpp \
                     ../../Classes/SIX_Framework/Net_Interface/SIX_ClientBase.cpp \
                     ../../Classes/SIX_Framework/Net_Interface/SIX_Http.cpp \
                      ../../Classes/SIX_Framework/Net_Interface/SIX_PackageMgr.cpp \
                     ../../Classes/SIX_Framework/Net_Interface/SIX_Proxy.cpp \
                     ../../Classes/SIX_Framework/Net_Interface/SIX_Socket.cpp \
                      ../../Classes/SIX_Framework/Net_Interface/SIX_SocketClient.cpp \
                     ../../Classes/SIX_Framework/Net_Interface/SIX_Thread.cpp \
                     ../../Classes/SIX_Framework/Shared_Interface/MiniDumper.cpp \
                     ../../Classes/SIX_Framework/Shared_Interface/SIX_CacheMgr.cpp \
                     ../../Classes/SIX_Framework/Shared_Interface/SIX_FileSystem.cpp \
                     ../../Classes/SIX_Framework/Shared_Interface/SIX_GlobalMgr.cpp \
                      ../../Classes/SIX_Framework/Shared_Interface/SIX_Logger.cpp \
                     ../../Classes/SIX_Framework/Shared_Interface/SIX_MusicMgr.cpp \
                     ../../Classes/SIX_Framework/Shared_Interface/SIX_UIMgr.cpp \
                     ../../Classes/SIX_Framework/Shared_Interface/SIX_UIScene.cpp \
                      ../../Classes/SIX_Framework/Shared_Interface/SIX_Utility.cpp \
                     ../../Classes/SIX_Framework/Shared_Interface/SIX_XMLParser.cpp \
                     ../../Classes/SIX_Framework/Shared_Interface/SmartRes.cpp \
                     ../../Classes/SIX_Framework/Six_tinyxml/tinystr.cpp \
                     ../../Classes/SIX_Framework/Six_tinyxml/tinyxml.cpp \
                     ../../Classes/SIX_Framework/Six_tinyxml/tinyxmlerror.cpp \
                     ../../Classes/SIX_Framework/Six_tinyxml/tinyxmlparser.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_Console.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_CountDown.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_Cursor.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_DisconnectBox.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_EditBox.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_EffectBatchNode.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_EffectPopWnd.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_ExpandLayer.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_ListView.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_ListViewCell.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_MsgBox.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_NumberBatchNode.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_PopWnd.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_Scissor.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_ScrollBar.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_Slider.cpp \
                     ../../Classes/SIX_Framework/UI_Interface/SIX_UILayer.cpp \
                   ../../Classes/HelloFishScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/SIX_Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../CocosDenshion
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../extensions
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../external/MMEAD
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../cocos2dx/cocoa
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../cocos2dx/platform/third_party/android/prebuilt/libMMEAD/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Six_Framework
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Six_Framework/Base_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Six_Framework/Shared_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Six_Framework/Net_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Six_Framework/UI_Interface
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Six_Framework/Six_tinyxml
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/SIX_Head

LOCAL_CFLAGS += $(TOOL_CFLAGS) -fpermissive
LOCAL_CFLAGS += -Wdeprecated-declarations
LOCAL_CFLAGS += -std=c++11
#LOCAL_CFLAGS += -DTIXML_USE_STL

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_testcpp_common
#LOCAL_WHOLE_STATIC_LIBRARIES += libMMEAD
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,F:/SixCocos2d-xVC2012/Cocos2d-x/2.0-x-2.03_branch_231_NoScript)
$(call import-add-path,F:/SixCocos2d-xVC2012/Cocos2d-x/2.0-x-2.03_branch_231_NoScript/cocos2dx/platform/third_party/android/prebuilt)
$(call import-module,CocosDenshion/android)
#$(call import-module,external/MMEAD)
$(call import-module,cocos2dx)
$(call import-module,extensions)

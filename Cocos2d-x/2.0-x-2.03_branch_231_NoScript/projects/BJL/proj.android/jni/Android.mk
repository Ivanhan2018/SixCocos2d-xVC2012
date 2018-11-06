LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   hellocpp/Jni_system.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/ans/AnsIO.cpp \
                   ../../Classes/ans/AnsLog.cpp \
                   ../../Classes/ans/AnsNew.cpp \
                   ../../Classes/ans/AnsPath.cpp \
                   ../../Classes/ans/AnsString.cpp \
                   ../../Classes/ans/AnsThread.cpp \
                   ../../Classes/C2DXShareSDK/C2DXShareSDK.cpp \
                   ../../Classes/C2DXShareSDK/Android/ShareSDKUtils.cpp \
                   ../../Classes/C2DXShareSDK/Android/JSON/CCJSONConverter.cpp \
                   ../../Classes/C2DXShareSDK/Android/JSON/cJSON/cJSON.c \
                   ../../Classes/common/DBHandler.cpp \
                   ../../Classes/common/Encrypt.cpp \
                   ../../Classes/common/JsonHelper.cpp \
                   ../../Classes/common/MyNSString.cpp \
                   ../../Classes/common/sqlite3.c \
                   ../../Classes/configMgr/ConfigMgr.cpp \
                   ../../Classes/controls/CCTouchSprite.cpp \
                   ../../Classes/controls/tableViewLayer.cpp \
                   ../../Classes/ddz/CardTableLayer.cpp  \
                   ../../Classes/ddz/DDZLogic.cpp  \
                   ../../Classes/ddz/DialogLayer.cpp  \
                   ../../Classes/ddz/GameTaskCommon.cpp  \
                   ../../Classes/ddz/JniControl.cpp  \
                   ../../Classes/ddz/MyTools.cpp  \
                   ../../Classes/ddz/SceneControl.cpp  \
                   ../../Classes/ddz/SceneData.cpp  \
                   ../../Classes/ddz/SceneLogic.cpp  \
                   ../../Classes/ddz/SceneView.cpp  \
                   ../../Classes/ddz/Settlement.cpp  \
                   ../../Classes/ddz/SetUpLayer.cpp  \
                   ../../Classes/ddz/SoundControl.cpp  \
                   ../../Classes/ddz/Timer.cpp  \
                   ../../Classes/ddz/User.cpp  \
                   ../../Classes/ddz/ViewCardEffect.cpp  \
                   ../../Classes/ddz/ViewHandCard.cpp  \
                   ../../Classes/ddz/ViewMenuLayer.cpp  \
                   ../../Classes/ddz/ViewTask.cpp  \
                   ../../Classes/ddz/VoiceAndFace.cpp  \
                   ../../Classes/ddz/CardManager.cpp  \
                   ../../Classes/ddz/OperalayerBJL.cpp  \
                   ../../Classes/ddz/ChipManager.cpp  \
                   ../../Classes/ddz/Tools.cpp  \
                   ../../Classes/ddz/CardSprite.cpp  \
                   ../../Classes/ddz/SceneTableInterfaceLayer.cpp  \
                   ../../Classes/entity/EntityMgr.cpp  \
                   ../../Classes/entity/Login.cpp  \
                   ../../Classes/entity/RoomFrame.cpp  \
                   ../../Classes/entity/UserItem.cpp  \
                   ../../Classes/event/GBEvent.cpp  \
                   ../../Classes/globalUnits/GlobalUnits.cpp  \
                   ../../Classes/gui/ActivityLayer.cpp  \
                   ../../Classes/gui/ActivitySprite.cpp  \
                   ../../Classes/gui/AgreementLayer.cpp  \
                   ../../Classes/gui/AgreementScrollView.cpp  \
                   ../../Classes/gui/BaseLayer.cpp  \
                   ../../Classes/gui/ChongCoinsLayer.cpp  \
                   ../../Classes/gui/ChoosePhotoCell.cpp  \
                   ../../Classes/gui/ChoosephotoScrollLayer.cpp  \
                   ../../Classes/gui/ChoosePlayerPhotoLayer.cpp  \
                   ../../Classes/gui/CShaderSprite.cpp  \
                   ../../Classes/gui/CustomerServiceLayer.cpp  \
                   ../../Classes/gui/CusTomTableViewCell.cpp  \
                   ../../Classes/gui/EmailCell.cpp  \
                   ../../Classes/gui/EmailLayer.cpp  \
                   ../../Classes/gui/EmailScorllLayer.cpp  \
                   ../../Classes/gui/ExchangerLayer.cpp  \
                   ../../Classes/gui/ExitLayer.cpp  \
                   ../../Classes/gui/FMGameItemLayer.cpp  \
                   ../../Classes/gui/FreeCell.cpp  \
                   ../../Classes/gui/FreeCoins.cpp  \
                   ../../Classes/gui/FreeLayer.cpp  \
                   ../../Classes/gui/FreeScrollLayer.cpp  \
                   ../../Classes/gui/FriendSystemLayer.cpp  \
                   ../../Classes/gui/GetCharge.cpp  \
                   ../../Classes/gui/GroupSprite.cpp  \
                   ../../Classes/gui/HelpLayer.cpp  \
                   ../../Classes/gui/HelpScrollView.cpp  \
                   ../../Classes/gui/LuckyDraw.cpp  \
                   ../../Classes/gui/LoadingLayer.cpp  \
                   ../../Classes/gui/LoginLayer.cpp  \
                   ../../Classes/gui/MenuLayer.cpp  \
                   ../../Classes/gui/MissionLayer.cpp  \
                   ../../Classes/gui/ModifyPassWord.cpp  \
                   ../../Classes/gui/MovingLabelLayer.cpp  \
                   ../../Classes/gui/OverRegistLayer.cpp  \
                   ../../Classes/gui/PlayerInfoLayer.cpp  \
                   ../../Classes/gui/PromptBox.cpp  \
                   ../../Classes/gui/PropLayer.cpp  \
                   ../../Classes/gui/RankSystemLayer.cpp  \
                   ../../Classes/gui/RechargeLayer.cpp  \
                   ../../Classes/gui/RegistLayer.cpp  \
                   ../../Classes/gui/RoomLayer.cpp  \
                   ../../Classes/gui/RoomOption.cpp  \
                   ../../Classes/gui/RuningBar.cpp  \
                   ../../Classes/gui/ShopSystemLayer.cpp  \
                   ../../Classes/gui/TabLayer.cpp  \
                   ../../Classes/gui/TaskInfo.cpp  \
                   ../../Classes/gui/VIPSystemLayer.cpp  \
                   ../../Classes/gui/WarningLayer.cpp  \
                   ../../Classes/msgDispatch/MsgDispatch.cpp  \
                   ../../Classes/net/GC_Socket.cpp  \
                   ../../Classes/net/TcpNetwork.cpp  \
                   ../../Classes/net/common.cpp  \
                   ../../Classes/serializers/geometry.cpp  \
                   ../../Classes/Json/lib_json/json_writer.cpp \
                   ../../Classes/Json/lib_json/json_value.cpp \
                   ../../Classes/Json/lib_json/json_reader.cpp \
                   ../../Classes/Json/lib_json/json_internalarray.inl \
                   ../../Classes/Json/lib_json/json_internalmap.inl \
                   ../../Classes/Json/lib_json/json_valueiterator.inl \
                   hellocpp/  

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                   $(LOCAL_PATH)/../../Classes/ans \
                   $(LOCAL_PATH)/../../Classes/C2DXShareSDK \
                   $(LOCAL_PATH)/../../Classes/C2DXShareSDK/Android \
                   $(LOCAL_PATH)/../../Classes/C2DXShareSDK/Android/JSON \
                   $(LOCAL_PATH)/../../Classes/C2DXShareSDK/Android/JSON/cJSON \
                   $(LOCAL_PATH)/../../Classes/common \
                   $(LOCAL_PATH)/../../Classes/configMgr \
                   $(LOCAL_PATH)/../../Classes/controls \
                   $(LOCAL_PATH)/../../Classes/ddz \
                   $(LOCAL_PATH)/../../Classes/entity \
                   $(LOCAL_PATH)/../../Classes/event \
                   $(LOCAL_PATH)/../../Classes/globalUnits \
                   $(LOCAL_PATH)/../../Classes/gui \
                   $(LOCAL_PATH)/../../Classes/msgDispatch \
                   $(LOCAL_PATH)/../../Classes/net \
                   $(LOCAL_PATH)/../../Classes/serializers \
                   $(LOCAL_PATH)/../../Classes/serializers \
                   $(LOCAL_PATH)/../../Classes/Json/ \
                   $(LOCAL_PATH)/../../../../iconv/include \
                   $(LOCAL_PATH)/../../../../iconv/libcharset \
                   $(LOCAL_PATH)/../../../../iconv/lib \
                   $(LOCAL_PATH)/../../../../iconv/libcharset/include \
                   $(LOCAL_PATH)/../../../../iconv/srclib \
                   $(LOCAL_PATH)/../../../../iconv

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += libiconv

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,iconv)

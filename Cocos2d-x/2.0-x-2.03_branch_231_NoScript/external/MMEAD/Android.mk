LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libMMEAD
 
LOCAL_CFLAGS := \
	-Wno-multichar \
	-D_ANDROID \
	-DLIBDIR=\"\" \
	-DBUILDING_LIBMMEAD \
	-DIN_LIBRARY

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/Miracl

##############################################
# ������͵��д���������ٰ�ÿ���ļ���дһ����:)  #
# Cool.Cat@2013/9/14 13:43:32                #
##############################################
# �ȱ���������Miracl
SRC_BATCH := $(wildcard $(LOCAL_PATH)/Miracl/*.c)
# �ٱ��벢���ӵ�MMEAD
SRC_BATCH += $(wildcard $(LOCAL_PATH)/*.cpp)
# �滻·��������wildcard��Ч
SRC_BATCH := $(SRC_BATCH:$(LOCAL_PATH)/%=%)
# just for debug print~~~
$(warning --+$(SRC_BATCH)+--)

LOCAL_SRC_FILES := \
	$(SRC_BATCH)

include $(BUILD_STATIC_LIBRARY)

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
# 下面是偷懒写法，无需再把每个文件都写一遍了:)  #
# Cool.Cat@2013/9/14 13:43:32                #
##############################################
# 先编译依赖库Miracl
SRC_BATCH := $(wildcard $(LOCAL_PATH)/Miracl/*.c)
# 再编译并链接到MMEAD
SRC_BATCH += $(wildcard $(LOCAL_PATH)/*.cpp)
# 替换路径，否则wildcard无效
SRC_BATCH := $(SRC_BATCH:$(LOCAL_PATH)/%=%)
# just for debug print~~~
$(warning --+$(SRC_BATCH)+--)

LOCAL_SRC_FILES := \
	$(SRC_BATCH)

include $(BUILD_STATIC_LIBRARY)

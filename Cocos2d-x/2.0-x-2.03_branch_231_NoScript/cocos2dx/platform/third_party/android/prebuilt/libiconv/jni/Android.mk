LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libiconv

LOCAL_CFLAGS := \
	-Wno-multichar \
	-D_ANDROID \
	-DLIBDIR=\"\" \
	-DBUILDING_LIBICONV \
	-DBUILDING_LIBCHARSET \
	-DHAVE_CONFIG_H \
	-DIN_LIBRARY

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/ \
	$(LOCAL_PATH)/include \
	$(LOCAL_PATH)/lib \
	$(LOCAL_PATH)/libcharset/include \
	$(LOCAL_PATH)/srclib

LOCAL_SRC_FILES := \
	libcharset/lib/localcharset.c \
	lib/iconv.c \
	lib/relocatable.c

include $(BUILD_STATIC_LIBRARY)
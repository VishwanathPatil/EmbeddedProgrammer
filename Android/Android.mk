# As of Android-14

# get current directory
LOCAL_PATH := $(call my-dir)

# clear all variables
include $(CLEAR_VARS)

LOCAL_MODULE := sample_exe
# extension of file matters, accordingly compiler used
# Don't include LOCAL_PATH for LOCAL_SRC_FILES since
# local path already assumed for LOCAL_SRC_FILES
LOCAL_SRC_FILES := sample_exe.cpp

# there is nothing called CPP_INCLUDES

LOCAL_C_INCLUDES := $(LOCAL_PATH)/inc system/libbase/include

LOCAL_SHARED_LIBRARIES = libbinder

LOCAL_C_FLAGS := -Wall -Werror

# include rules for building executable, other option building shared library
# static library etc
include $(BUILD_EXECUTABLE)


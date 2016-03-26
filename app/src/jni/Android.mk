LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# Change the build output to the specific directory
TARGET_OUT = ../main/jniLibs/$(TARGET_ARCH_ABI)

LOCAL_MODULE    := sdtmemadj
#LOCAL_C_INCLUDES += $(LOCAL_PATH)

LOCAL_SRC_FILES += main.cpp sdt_list.cpp
include $(BUILD_EXECUTABLE)
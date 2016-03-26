LOCAL_PATH := $(call my-dir)

#include $(CLEAR_VARS)
#SDT_NDK_PATH := /home/raycad/Android/android-ndk-r11b/sources/cxx-stl/gnu-libstdc++/4.9/libs
#LOCAL_MODULE := gnustl_shared
#LOCAL_SRC_FILES := $(SDT_NDK_PATH)/$(TARGET_ARCH_ABI)/libgnustl_shared.so
#include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
# Use the flags to switch to use the stuff as the shared library or the executable
SDT_USE_SHARED := true

# Change the build output to the specific directory
TARGET_OUT = ../main/jniLibs/$(TARGET_ARCH_ABI)

LOCAL_MODULE    := sdtmemadj
#LOCAL_C_INCLUDES += $(LOCAL_PATH)

ifeq ($(SDT_USE_SHARED), true)
LOCAL_SRC_FILES += mem_adjustment.c sdt_list.cpp
else
LOCAL_SRC_FILES += main.cpp sdt_list.cpp
endif

#LOCAL_SHARED_LIBRARIES := gnustl_shared

ifeq ($(SDT_USE_SHARED), true)
include $(BUILD_SHARED_LIBRARY)
else
include $(BUILD_EXECUTABLE)
endif
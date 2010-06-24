# Copyright (C) 2007 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH:= $(call my-dir)

ifneq ($(TARGET_SIMULATOR),true)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := board.c panel.c keypad.c usb.c

LOCAL_C_INCLUDES := $(call include-path-for, bootloader)

LOCAL_CFLAGS := -O2 -g -W -Wall
LOCAL_CFLAGS += -march=armv6

LOCAL_MODULE := libboot_board_hero

include $(BUILD_RAW_STATIC_LIBRARY)

endif # !TARGET_SIMULATOR


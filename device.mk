#
# Copyright (C) 2009 The Android Open-Source Project
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
#

# To be included directly by a product makefile; do not use inherit-product.

DEVICE_PACKAGE_OVERLAYS := vendor/htc/hero/overlay

PRODUCT_COPY_FILES += \
	vendor/htc/hero/proprietary/AudioPara4.csv:system/etc/AudioPara4.csv \
	vendor/htc/hero/proprietary/AudioFilter.csv:system/etc/AudioFilter.csv \
	vendor/htc/hero/proprietary/AudioPreProcess.csv:system/etc/AudioPreProcess.csv \
	vendor/htc/hero/proprietary/gps.conf:system/etc/gps.conf

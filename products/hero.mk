#
# Copyright (C) 2009 The Android Open Source Project
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

# This is the top-level configuration for a Hero CyanogenMod build

$(call inherit-product, build/target/product/generic.mk)

ifeq ($(PRODUCT_REGION_EU),true)

PRODUCT_PROPERTY_OVERRIDES := \
	    ro.com.android.dateformat=dd-MM-yyyy \
        ro.com.android.dataroaming=true \
        ro.ril.hsxpa=2 \
        ro.ril.gprsclass=12
        
else

PRODUCT_PROPERTY_OVERRIDES := \
	    ro.com.android.dateformat=MM-dd-yyyy \
        ro.com.android.dataroaming=true \
        ro.ril.hsxpa=1 \
        ro.ril.gprsclass=10
endif

PRODUCT_PROPERTY_OVERRIDES += \
        keyguard.no_require_sim=true

PRODUCT_NAME := hero
PRODUCT_BRAND := HTC
PRODUCT_DEVICE := hero
PRODUCT_MODEL := AOSP Hero
PRODUCT_MANUFACTURER := HTC
PRODUCT_BUILD_PROP_OVERRIDES := BUILD_ID=ERE36B PRODUCT_NAME=hero BUILD_FINGERPRINT=google/passion/passion/mahimahi:2.1-update1/ERE27/24178:user/release-keys

PRODUCT_POLICY := android.policy_phone

WITH_DEXPREOPT := true
DISABLE_DEXPREOPT := false
WITH_DEXPREOPT_buildbot := true

# Build WebKit with V8
JS_ENGINE:=v8
 
# Used by BusyBox
KERNEL_MODULES_DIR:=/system/lib/modules
   
USE_CAMERA_STUB := false

PRODUCT_PACKAGES := \
    AlarmProvider \
    ApplicationsProvider \
    AccountAndSyncSettings \
    Bluetooth \
    Browser \
    Bugreport \
    Calculator \
    Calendar \
    CalendarProvider \
    Camera \
    CertInstaller \
    Contacts \
    ContactsProvider \
    DownloadProvider \
    DrmProvider \
    Email \
    FieldTest \
    GlobalSearch \
    GoogleSearch \
    HTMLViewer \
    Launcher \
    MediaProvider \
    Mms \
    Music \
    PackageInstaller \
    Phone \
    PicoTts \
    Settings \
    SettingsProvider \
    SoundRecorder \
    Stk \
    SubscribedFeedsProvider \
    Sync \
    SyncProvider \
    TelephonyProvider \
    TtsService \
    Updater \
    UserDictionaryProvider \
    VoiceDialer \
    VpnServices \
    WebSearchProvider \
    framework-res

PRODUCT_PACKAGES += \
    DeskClock \
    Gallery3D \
    LiveWallpapers \
    LiveWallpapersPicker \
    libRS \
    librs_jni
    
PRODUCT_PACKAGES += Superuser

# Build WebKit with V8
JS_ENGINE=v8

# Pick up some sounds
include frameworks/base/data/sounds/AudioPackage4.mk

PRODUCT_COPY_FILES += \
    vendor/htc/hero/prebuilt/system/lib/libspeech.so:system/lib/libspeech.so \
    vendor/cyanogen/prebuilt/common/etc/apns-conf.xml:system/etc/apns-conf.xml \
    vendor/cyanogen/prebuilt/common/etc/dnsmasq.conf:system/etc/dnsmasq.conf \
    vendor/cyanogen/prebuilt/common/etc/fstab:system/etc/fstab \
    vendor/cyanogen/prebuilt/common/etc/sysctl.conf:system/etc/sysctl.conf \
    vendor/cyanogen/prebuilt/common/etc/init.d/00banner:system/etc/init.d/00banner \
    vendor/cyanogen/prebuilt/common/etc/init.d/01sysctl:system/etc/init.d/01sysctl \
    vendor/cyanogen/prebuilt/common/etc/init.d/03firstboot:system/etc/init.d/03firstboot \
    vendor/cyanogen/prebuilt/common/etc/init.d/20userinit:system/etc/init.d/20userinit \
    vendor/cyanogen/prebuilt/common/etc/init.d/99complete:system/etc/init.d/99complete \
    vendor/cyanogen/prebuilt/common/etc/permissions/android.hardware.camera.autofocus.xml:system/etc/permissions/android.hardware.camera.autofocus.xml \
    vendor/cyanogen/prebuilt/common/etc/permissions/android.hardware.touchscreen.multitouch.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.xml \
    vendor/htc/hero/prebuilt/system/etc/permissions/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    vendor/htc/hero/prebuilt/system/etc/permissions/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    vendor/htc/hero/prebuilt/system/etc/permissions/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml \
    vendor/htc/hero/prebuilt/system/etc/permissions/android.software.live_wallpaper.xml:system/etc/permissions/android.software.live_wallpaper.xml \
    vendor/cyanogen/prebuilt/common/bin/fix_permissions:system/bin/fix_permissions \
    vendor/cyanogen/prebuilt/common/bin/usb-tether:system/bin/usb-tether \
    vendor/cyanogen/prebuilt/common/bin/shutdown:system/bin/shutdown \
    vendor/cyanogen/prebuilt/common/bin/compcache:system/bin/compcache
    
ifdef WITH_HTC_KEYBOARD
    PRODUCT_COPY_FILES += \
        vendor/cyanogen/proprietary/HTC_IME.apk:system/app/HTC_IME.apk \
	    vendor/cyanogen/proprietary/libt9.so:system/lib/libt9.so
endif

ifdef WITH_GOOGLE
    PRODUCT_COPY_FILES += \
        vendor/cyanogen/proprietary/BugReport.apk:system/app/BugReport.apk \
        vendor/cyanogen/proprietary/CarDock.apk:system/app/CarDock.apk \
        vendor/cyanogen/proprietary/com.amazon.mp3.apk:system/app/com.amazon.mp3.apk \
        vendor/cyanogen/proprietary/EnhancedGoogleSearchProvider.apk:system/app/EnhancedGoogleSearchProvider.apk \
        vendor/cyanogen/proprietary/Facebook.apk:system/app/Facebook.apk \
        vendor/cyanogen/proprietary/GenieWidget.apk:system/app/GenieWidget.apk \
        vendor/cyanogen/proprietary/Gmail.apk:system/app/Gmail.apk \
        vendor/cyanogen/proprietary/GmailProvider.apk:system/app/GmailProvider.apk \
        vendor/cyanogen/proprietary/GoogleApps.apk:system/app/GoogleApps.apk \
        vendor/cyanogen/proprietary/GoogleBackupTransport.apk:system/app/GoogleBackupTransport.apk \
        vendor/cyanogen/proprietary/GoogleCheckin.apk:system/app/GoogleCheckin.apk \
        vendor/cyanogen/proprietary/GoogleContactsSyncAdapter.apk:system/app/GoogleContactsSyncAdapter.apk \
        vendor/cyanogen/proprietary/GoogleGoggles.apk:system/app/GoogleGoggles.apk \
        vendor/cyanogen/proprietary/GooglePartnerSetup.apk:system/app/GooglePartnerSetup.apk \
        vendor/cyanogen/proprietary/GoogleSettingsProvider.apk:system/app/GoogleSettingsProvider.apk \
        vendor/cyanogen/proprietary/GoogleSubscribedFeedsProvider.apk:system/app/GoogleSubscribedFeedsProvider.apk \
        vendor/cyanogen/proprietary/googlevoice.apk:system/app/googlevoice.apk \
        vendor/cyanogen/proprietary/gtalkservice.apk:system/app/gtalkservice.apk \
        vendor/cyanogen/proprietary/HtcCopyright.apk:system/app/HtcCopyright.apk \
        vendor/cyanogen/proprietary/LatinImeTutorial.apk:system/app/LatinImeTutorial.apk \
        vendor/cyanogen/proprietary/Maps.apk:system/app/Maps.apk \
        vendor/cyanogen/proprietary/MarketUpdater.apk:system/app/MarketUpdater.apk \
        vendor/cyanogen/proprietary/MediaUploader.apk:system/app/MediaUploader.apk \
        vendor/cyanogen/proprietary/NetworkLocation.apk:system/app/NetworkLocation.apk \
        vendor/cyanogen/proprietary/PassionQuickOffice.apk:system/app/PassionQuickOffice.apk \
        vendor/cyanogen/proprietary/SetupWizard.apk:system/app/SetupWizard.apk \
        vendor/cyanogen/proprietary/Street.apk:system/app/Street.apk \
        vendor/cyanogen/proprietary/Talk.apk:system/app/Talk.apk \
        vendor/cyanogen/proprietary/TalkProvider.apk:system/app/TalkProvider.apk \
        vendor/cyanogen/proprietary/Vending.apk:system/app/Vending.apk \
        vendor/cyanogen/proprietary/VoiceSearchWithKeyboard.apk:system/app/VoiceSearchWithKeyboard.apk \
        vendor/cyanogen/proprietary/YouTube.apk:system/app/YouTube.apk \
        vendor/cyanogen/proprietary/com.google.android.datamessaging.xml:system/etc/permissions/com.google.android.datamessaging.xml \
        vendor/cyanogen/proprietary/com.google.android.gtalkservice.xml:system/etc/permissions/com.google.android.gtalkservice.xml \
        vendor/cyanogen/proprietary/com.google.android.maps.xml:system/etc/permissions/com.google.android.maps.xml \
        vendor/cyanogen/proprietary/com.google.android.gtalkservice.jar:system/framework/com.google.android.gtalkservice.jar \
        vendor/cyanogen/proprietary/com.google.android.maps.jar:system/framework/com.google.android.maps.jar \
        vendor/cyanogen/proprietary/libgtalk_jni.so:system/lib/libgtalk_jni.so \
        vendor/cyanogen/proprietary/libinterstitial.so:system/lib/libinterstitial.so
else    
    PRODUCT_PACKAGES += \
        Provision \
        GoogleSearch \
        LatinIME
endif

include external/svox/pico/lang/PicoLangDeDeInSystem.mk
include external/svox/pico/lang/PicoLangEnGBInSystem.mk
include external/svox/pico/lang/PicoLangEnUsInSystem.mk
include external/svox/pico/lang/PicoLangEsEsInSystem.mk
include external/svox/pico/lang/PicoLangFrFrInSystem.mk
include external/svox/pico/lang/PicoLangItItInSystem.mk

PRODUCT_LOCALES := \
    en_US \
    ar_EG \
    ar_IL \
    bg_BG \
    ca_ES \
    cs_CZ \
    da_DK \
    de_AT \
    de_CH \
    de_DE \
    de_LI \
    el_GR \
    en_AU \
    en_CA \
    en_GB \
    en_IE \
    en_IN \
    en_NZ \
    en_SG \
    en_ZA \
    es_ES \
    es_US \
    fi_FI \
    fr_BE \
    fr_CA \
    fr_CH \
    fr_FR \
    he_IL \
    hi_IN \
    hr_HR \
    hu_HU \
    id_ID \
    it_CH \
    it_IT \
    iw_IL \
    ja_JP \
    ko_KR \
    lt_LT \
    lv_LV \
    nb_NO \
    nl_BE \
    nl_NL \
    pl_PL \
    pt_BR \
    pt_PT \
    ro_RO \
    ru_RU \
    sk_SK \
    sl_SI \
    sr_RS \
    sv_SE \
    th_TH \
    tl_PH \
    tr_TR \
    uk_UA \
    vi_VN \
    zh_CN \
    zh_TW

#PRODUCT_COPY_FILES +=  \
#    vendor/cyanogen/prebuilt/passion/media/bootanimation.zip:system/media/bootanimation.zip



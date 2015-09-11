LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


$(call import-add-path,$(LOCAL_PATH)/../../../fplay/client/cocos2d/cocos/prebuilt-mk)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Constants.cpp \
                   ../../Classes/GlobalVar.cpp \
                   ../../Classes/IntroScreen.cpp \
                   ../../Classes/WordedApp.cpp \
                   ../../Classes/onemode/OneScreen.cpp \
                   ../../Classes/intro/IntroItem.cpp \
                   ../../Classes/base/Dlg.cpp \
                   ../../Classes/base/DlgMgr.cpp \
                   ../../Classes/base/ParticleMgr.cpp \
                   ../../Classes/base/util/ad.cpp \
                   ../../Classes/base/util/common.cpp \
                   ../../Classes/base/util/graphic.cpp \
                   ../../Classes/base/util/effects.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

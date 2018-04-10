LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/LevelChooserScene.cpp \
				   ../../Classes/AbstractMatchLogic.cpp \
				   ../../Classes/AbstractRiverCross.cpp \
				   ../../Classes/MainBlockScene.cpp \
				   ../../Classes/MatchLogicScene.cpp \
				   ../../Classes/RiverCrossingScene.cpp \
				   ../../Classes/RiverCrossingSceneThird.cpp \
				   ../../Classes/RiverCrossingSceneFour.cpp \
				   ../../Classes/TestExtends.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)

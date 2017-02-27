//
// Created by Administrator on 2017/2/27.
//

#ifndef __ANDROIDLOG_H__
#define __ANDROIDLOG_H__

#include <jni.h>
#include <android/log.h>

#define LOG_TAG		"LOLILA"

#define LOGI(...)	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...)	__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...)	__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define	LOGE(...)	__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //DEMO_ANDROIDLOG_H

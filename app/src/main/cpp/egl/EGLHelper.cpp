/**
 *@author: baizf
 *@date: 2023/2/24
*/
//

#include "EGLHelper.h"
#include "Logutils.h"
#include <exception>

/*
 * 步骤：
 * 1、得到默认显示设备，即屏幕窗口
 * 2、初始化默认显示设备
 * 3、配置显示设备的属性
 *  4、检查运行设备是否支持显示设备的属性列表,获取EGLConfig
 *  5、创建EGLContext
 *  6、创建渲染的surface
 *  7、绑定EGLContext和EGLSurface到EGLDisplay
 * */
int EGLHelper::init(EGLNativeWindowType surface) {
    mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    if (mEGLDisplay == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay  error");
        return -1;
    }
    EGLint major; //主要版本
    EGLint minor; //次要版本
    if (!eglInitialize(mEGLDisplay, &major, &minor)) {
        LOGE("eglInitialize error");
        return -1;
    }
    LOGI("major=%d, minor=%d", major, minor);

    //配置属性列表数组，结尾以EGL_NONE结束
    const EGLint attributeConfigList[] = {
            EGL_BUFFER_SIZE, 32,
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 8, //深度缓冲区占用8位
            EGL_STENCIL_SIZE, 8, //模板缓冲区占用8位
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT, //EGL渲染类型：OpenGL ES3
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_NONE
    };

    EGLint numConfigs;
    EGLConfig eglConfig = nullptr;

    EGLBoolean result = eglChooseConfig(mEGLDisplay,
                                        attributeConfigList, //指定配置匹配所需的属性。
                                        &eglConfig, //帧缓冲区配置的数组。
                                        1, //指定帧缓冲区配置数组的大小。
                                        &numConfigs); //返回的帧缓冲区配置数。
    if (!result) {
        LOGE("eglChooseConfig attributeConfigList error");
        return -1;
    } else if (result == EGL_BAD_ATTRIBUTE) {
        LOGI("eglChooseConfig attributeConfigList fail attribute_list contains an invalid frame buffer configuration attribute or an attribute value that is unrecognized or out of range.");
    } else if (result == EGL_BAD_DISPLAY) {
        LOGI("eglChooseConfig attributeConfigList fail display is not an EGL display connection");
    } else if (result == EGL_NOT_INITIALIZED) {
        LOGI("eglChooseConfig attributeConfigList fail display has not been initialized.");
    } else if (result == EGL_BAD_PARAMETER) {
        LOGI("eglChooseConfig attributeConfigList fail num_config is NULL.");
    }
    LOGI("frame buffer configurations number=%d",numConfigs);

    const EGLint contextAttribList[] = {
            EGL_CONTEXT_CLIENT_VERSION, 3, //确定OpenGL ES版本为3.x
            EGL_NONE
    };
    mEGLContext = eglCreateContext(mEGLDisplay, eglConfig, nullptr, contextAttribList);
    if (mEGLContext == EGL_NO_CONTEXT) {
        LOGE("eglCreateContext error");
        return -1;
    }

    mEGLSurface = eglCreateWindowSurface(mEGLDisplay, eglConfig, surface, nullptr);
    if (mEGLSurface == EGL_NO_SURFACE) {
        LOGE("eglCreateWindowSurface error");
        return -1;
    }

    result = eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext);
    if (!result) {
        LOGE("eglMakeCurrent error");
        return -1;
    }
    LOGI("eglMakeCurrent success");
    return 0;
}

int EGLHelper::swapBuffers() const {
    if (mEGLDisplay != EGL_NO_DISPLAY && mEGLSurface != EGL_NO_SURFACE) {
        eglSwapBuffers(mEGLDisplay, mEGLSurface);
        return 0;
    }
    return -1;
}

void EGLHelper::destroyEGL() {
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        // 解绑display上的eglContext和Surface
        eglMakeCurrent(mEGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (mEGLContext != EGL_NO_CONTEXT) {
            eglDestroyContext(mEGLDisplay, mEGLContext);
            mEGLContext = EGL_NO_CONTEXT;
        }
        if (mEGLSurface != EGL_NO_SURFACE) {
            eglDestroySurface(mEGLDisplay, mEGLSurface);
            mEGLSurface = EGL_NO_SURFACE;
        }
        if (mEGLDisplay != EGL_NO_DISPLAY) {
            eglTerminate(mEGLDisplay);
            mEGLDisplay = EGL_NO_DISPLAY;
        }
    }
}
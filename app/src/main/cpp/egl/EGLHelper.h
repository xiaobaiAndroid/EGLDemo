/**
 *@author: baizf
 *@date: 2023/2/24
*/
//

#ifndef EGLSAMPLE_EGLHELPER_H
#define EGLSAMPLE_EGLHELPER_H

#include <EGL/egl.h>

class EGLHelper{
public:
    EGLContext mEGLContext = EGL_NO_CONTEXT;
    EGLDisplay mEGLDisplay = EGL_NO_DISPLAY;
    EGLSurface mEGLSurface = EGL_NO_SURFACE;


    int init(EGLNativeWindowType surface);

    int swapBuffers() const;

    void destroyEGL();
};


#endif //EGLSAMPLE_EGLHELPER_H

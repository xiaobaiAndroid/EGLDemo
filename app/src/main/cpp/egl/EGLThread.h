/**
 *@author: baizf
 *@date: 2023/2/24
*/
//

#ifndef EGLSAMPLE_EGLTHREAD_H
#define EGLSAMPLE_EGLTHREAD_H

#include "EGLHelper.h"
#include <pthread.h>

//自动渲染
#define RENDER_MODULE_AUTO 1
//手动渲染
#define RENDER_MODULE_MANUAL 2

class EGLThread{
public:

    pthread_t mThread = -1;
    pthread_mutex_t mPthreadMutex;
    pthread_cond_t mPthreadCondition;

    EGLNativeWindowType mWindow;

    bool isExit = false;
    bool isCreate = false;
    bool isStart = false;
    bool isChange = false;

    int mSurfaceWidth = 0;
    int mSurfaceHeight = 0;

    int mRenderType = RENDER_MODULE_AUTO;

    typedef void (*OnCreate)();
    OnCreate mOnCreate;

    typedef void (*OnChange)(int width, int height);
    OnChange mOnChange;

    typedef void (*OnDraw)();
    OnDraw mOnDraw;

    EGLThread();
    ~EGLThread();

    void onSurfaceCreate(EGLNativeWindowType window);
    void onSurfaceChange(int width, int height);

    //设置模式
    void setRenderModule(int renderModule);
    void notifyRender();


    void setOnCreateCallBack(OnCreate onCreate);
    void setOnChangeCallBack(OnChange onChange);
    void setOnDraw(OnDraw onDraw);

};

#endif //EGLSAMPLE_EGLTHREAD_H

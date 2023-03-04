/**
 *@author: baizf
 *@date: 2023/2/24
*/
//

#include "EGLThread.h"
#include "Logutils.h"
#include <unistd.h>


EGLThread::EGLThread() {
    pthread_mutex_init(&mPthreadMutex, nullptr);
    pthread_cond_init(&mPthreadCondition, nullptr);
}

EGLThread::~EGLThread() {
    pthread_mutex_destroy(&mPthreadMutex);
    pthread_cond_destroy(&mPthreadCondition);
}


void *run(void *context) {
    auto *pThread = static_cast<EGLThread *>(context);
    if(!pThread){
        LOGD("EGLThread is null");
        pthread_exit(nullptr);
    }

    auto *pHelper = new EGLHelper();
    if(pHelper->init(pThread->mWindow) != 0){
        LOGE("EGLHelper init error");
        pthread_exit(nullptr);
    }

    while (!pThread->isExit){

        if(pThread->isCreate){
            pThread->isCreate = false;
            pThread->mOnCreate();
        }
        if(pThread->isChange){
            pThread->isChange = false;
            pThread->isStart = true;
            pThread->mOnChange(pThread->mSurfaceWidth, pThread->mSurfaceHeight);
        }

        if(pThread->isStart){
            pThread->mOnDraw();
            //交换缓冲区,显示到窗口
            pHelper->swapBuffers();

            if(pThread->mRenderType == RENDER_MODULE_AUTO){
                // sleep 1/60秒，近似1秒绘制60帧
                usleep(1000000/60);
            }else{
                pthread_mutex_lock(&pThread->mPthreadMutex);
                pthread_cond_wait(&pThread->mPthreadCondition, &pThread->mPthreadMutex);
                pthread_mutex_unlock(&pThread->mPthreadMutex);
            }
        }

    }
    pThread->mOnDestroy();
    pHelper->destroyEGL();
    delete pHelper;
    pthread_exit(nullptr);
}

void EGLThread::onSurfaceCreate(EGLNativeWindowType window) {
    if(mThread == -1){
        isCreate = true;
        mWindow = window;

        pthread_attr_t attr;
        ////初始化和设置线程分离属性,声明成joinable的线程，可以被其他线程join。
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        int result = pthread_create(&mThread, &attr, run, this);
        if(result != 0){
            LOGE("pthread_create error");
        }
        pthread_attr_destroy(&attr);
    }
}



void EGLThread::onSurfaceChange(int width, int height) {
    if(mThread != -1){
        mSurfaceWidth = width;
        mSurfaceHeight = height;
        isChange = true;
    }
    notifyRender();
}

void EGLThread::setRenderModule(int renderModule) {
    mRenderType = renderModule;
    notifyRender();
}

void EGLThread::notifyRender() {
    pthread_mutex_lock(&mPthreadMutex);
    pthread_cond_signal(&mPthreadCondition);
    pthread_mutex_unlock(&mPthreadMutex);
}

void EGLThread::setOnCreateCallBack(OnCreate onCreate) {
    mOnCreate = onCreate;
}

void EGLThread::setOnChangeCallBack(OnChange onChange) {
    mOnChange = onChange;
}

void EGLThread::setOnDraw(OnDraw onDraw) {
    mOnDraw = onDraw;
}

void EGLThread::setOnDestroy(OnDestroy onDestroy) {
    mOnDestroy = onDestroy;
}
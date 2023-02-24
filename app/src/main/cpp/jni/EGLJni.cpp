#include <jni.h>

/**
 *@author: baizf
 *@date: 2023/2/24
*/
//

#include "EGLThread.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <GLES3/gl31.h>

static EGLThread *eglThread = nullptr;

void onCreateCallBack(){

}

void onChangeCallBack(int width, int height){

}
void onDrawCallBack(){
    glClearColor(1.0f,0.0f,1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzf_egldemo_EGLSurfaceView_nSurfaceCreated(JNIEnv *env, jobject thiz, jobject surface) {


    eglThread = new EGLThread();
    eglThread->setOnCreateCallBack(onCreateCallBack);
    eglThread->setOnChangeCallBack(onChangeCallBack);
    eglThread->setOnDraw(onDrawCallBack);
    eglThread->setRenderModule(RENDER_MODULE_AUTO);

    ANativeWindow *pWindow = ANativeWindow_fromSurface(env, surface);
    eglThread->onSurfaceCreate(pWindow);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_bzf_egldemo_EGLSurfaceView_nSurfaceChanged(JNIEnv *env, jobject thiz, jint width,
                                                      jint height) {
    if(eglThread){
        eglThread->onSurfaceChange(width,height);
    }

}
extern "C"
JNIEXPORT void JNICALL
Java_com_bzf_egldemo_EGLSurfaceView_nSurfaceDestroyed(JNIEnv *env, jobject thiz) {
    if(eglThread){
        eglThread->isExit = true;

        pthread_join(eglThread->mThread, nullptr);

        delete eglThread;
        eglThread = nullptr;
    }

}
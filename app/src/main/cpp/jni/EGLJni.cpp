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
#include "TriangleSampler.h"

static EGLThread *eglThread = nullptr;

static TriangleSampler *triangleSampler = nullptr;

void onCreateCallBack(){
    if(triangleSampler){
        delete triangleSampler;
    }
    triangleSampler = new TriangleSampler();
}

void onChangeCallBack(int width, int height){

}
void onDrawCallBack(){
    triangleSampler->draw();
}

void onDestroy(){
    if(triangleSampler){
        delete triangleSampler;
        triangleSampler = nullptr;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_bzf_egldemo_EGLSurfaceView_nSurfaceCreated(JNIEnv *env, jobject thiz, jobject surface) {



    eglThread = new EGLThread();
    eglThread->setOnCreateCallBack(onCreateCallBack);
    eglThread->setOnChangeCallBack(onChangeCallBack);
    eglThread->setOnDraw(onDrawCallBack);
    eglThread->setOnDestroy(onDestroy);
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
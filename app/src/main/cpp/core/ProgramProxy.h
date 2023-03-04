/**
 *@author: baizf
 *@date: 2022/12/12
*/
//

#ifndef OPENGLDEMO_PROGRAMPROXY_H
#define OPENGLDEMO_PROGRAMPROXY_H

#include <GLES3/gl31.h>
#include <GLES3/gl3ext.h>
#include <jni.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <string>

using namespace std;

class ProgramProxy {
private:

    bool checkGlError(string &funcName);

    GLuint createShader(GLenum shaderType, string &src);

    GLuint createProgram(string &vertexSrc, string &fragmentSrc);

public:
    GLuint mProgram;


    static void clearBuffer();
    static void clearColor(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f);

    AAsset *loadAsset(JNIEnv *env, jobject *assetManager, string &path);

    bool openGLSLFile(JNIEnv *env, jobject *assetManager, string &path, string &src);

    ProgramProxy(JNIEnv *env, jobject *assetManager, string &vertexSrcPath,
                 string &fragmentSrcPath);

    ProgramProxy(string &vertexSrc,
                 string &fragmentSrc);

    ~ProgramProxy();

    void destroy();

    void use();
};

#endif //OPENGLDEMO_PROGRAMPROXY_H

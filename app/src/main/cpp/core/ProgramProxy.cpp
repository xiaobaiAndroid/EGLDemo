/**
 *@author: baizf
 *@date: 2022/12/12
*/
//

#include <cstdlib>
#include "ProgramProxy.h"
#include "Logutils.h"


ProgramProxy::ProgramProxy(string &vertexSrc, string &fragmentSrc) {
    mProgram = ProgramProxy::createProgram(vertexSrc, fragmentSrc);
}

ProgramProxy::ProgramProxy(JNIEnv *env, jobject *assetManager, string &vertexSrcPath,
                           string &fragmentSrcPath) {

    mProgram = 0;

    string vertSrc;
   bool isSuccess = ProgramProxy::openGLSLFile(env, assetManager, vertexSrcPath, vertSrc);
    if(!isSuccess){
        LOGE("load vertexSrcPath fail");
        return;
    }

    string fragSrc;
    isSuccess = ProgramProxy::openGLSLFile(env, assetManager, fragmentSrcPath, fragSrc);
    if(!isSuccess){
        LOGE("load fragSrcPath fail");
        return;
    }
    mProgram = ProgramProxy::createProgram(vertSrc, fragSrc);
}

ProgramProxy::~ProgramProxy() = default;


void ProgramProxy::destroy() {
    if(mProgram){
        glDeleteProgram(mProgram);
        mProgram = 0;
    }
}

GLuint ProgramProxy::createProgram(string &vertexSrc, string &fragmentSrc) {

    GLuint program = glCreateProgram();
    if (!program) {
        checkGlError((string &) "glCreateProgram");
        return program;
    }

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexSrc);

    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentSrc);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        LOGE("不能链接程序");
        GLint infoLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0) {
            char *infoLog = static_cast<char *>(malloc(infoLen));
            glGetProgramInfoLog(program, infoLen, nullptr, infoLog);
            LOGE("不能链接到程序：\n%s", infoLog);
            free(infoLog);
        }
        glDeleteProgram(program);
        program = GL_NONE;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void ProgramProxy::clearBuffer() {
    //GL_DEPTH_BUFFER_BIT：清除深度缓存数据
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ProgramProxy::clearColor(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
}


GLuint ProgramProxy::createShader(GLenum shaderType, string &src) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader) {
        checkGlError((string &) "glCreateShader");
        return 0;
    }
    const char *str = src.c_str();
    //为Shader添加源代码
    glShaderSource(shader, 1, &str, nullptr);

    glCompileShader(shader);
    GLint result = GL_FALSE;
    //验证编译是否成功
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        GLint infoLength = 0;
        //错误原因字符串长度
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
        if (infoLength > 0) {
            char *infoLog = static_cast<char *>(malloc(infoLength));
            if (infoLog) {
                glGetShaderInfoLog(shader, infoLength, nullptr, infoLog);
                LOGE("不能编译：%s Shader: \n%s\n",
                     shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment", infoLog);
                free(infoLog);
            }
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

bool ProgramProxy::checkGlError(string &funcName) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        LOGE("GL error after %s(): 0x%08x\n", funcName.c_str(), error);
        return true;
    }
    return false;
}


AAsset *ProgramProxy::loadAsset(JNIEnv *env, jobject *assetManager, string &path) {
    AAssetManager *nativeManager = AAssetManager_fromJava(env, *assetManager);
    if (nativeManager == nullptr) {
        return nullptr;
    }
    LOGD("GLUtils::openGLSLFile path [%s]", path.c_str());
    return AAssetManager_open(nativeManager, path.c_str(), AASSET_MODE_UNKNOWN);
}


bool ProgramProxy::openGLSLFile(JNIEnv *env, jobject *assetManager, string &path, string &src) {
    AAsset *asset = loadAsset(env, assetManager, path);
    if (asset == nullptr) {
        LOGD("Couldn't load %s", path.c_str());
        return false;
    }else{
        off_t length = AAsset_getLength(asset);
        char buffer[length + 1];
        int num = AAsset_read(asset, buffer, length);
        AAsset_close(asset);
        if (num != length) {
            LOGD("Couldn't read %s", path.c_str());
        }
        buffer[length] = '\0';
        src.append(buffer);
        return true;
    }

}

void ProgramProxy::use() {
    glUseProgram(mProgram);
}

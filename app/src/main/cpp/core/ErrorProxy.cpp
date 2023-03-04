/**
 *@author: baizf
 *@date: 2022/12/4
*/
//

#include "ErrorProxy.h"
#include <GLES3/gl31.h>
#include <Logutils.h>


void ErrorProxy::checkError(string message) {
    GLenum error = glGetError();
    if(error == GL_INVALID_ENUM){
        LOGE("GLenum 参数超出范围 %s", message.c_str());
    } else if(error == GL_INVALID_VALUE){
        LOGE("数值参数超出范围 %s", message.c_str());
    } else if(error == GL_INVALID_OPERATION){
        LOGE("当前状态下不允许执行指定的操作 %s", message.c_str());
    } else if(error == GL_INVALID_FRAMEBUFFER_OPERATION){
        LOGE("framebuffer对象不完整 %s", message.c_str());
    }else if(error == GL_OUT_OF_MEMORY){
        LOGE("内存不足 %s", message.c_str());
    }
}
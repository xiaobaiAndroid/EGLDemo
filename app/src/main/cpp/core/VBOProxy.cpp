/**
 *@author: baizf
 *@date: 2022/12/3
*/
//

#include "VBOProxy.h"
#include "ErrorProxy.h"

VBOProxy::VBOProxy(const void *vertices, const unsigned int arrSize) {
    glGenBuffers(1, &mVBO);
    bind();
    glBufferData(GL_ARRAY_BUFFER, //目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上
                 sizeof(float) * arrSize, //指定传输数据的大小(以字节为单位)
                 vertices, //实际数据
                 GL_STATIC_DRAW); //指定了我们希望显卡如何管理给定的数据, GL_STATIC_DRAW: 数据不会或几乎不会改变。

    ErrorProxy::checkError("glBufferData mVBO");
}

void VBOProxy::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
}

void VBOProxy::destroy() {
    glDeleteBuffers(1, &mVBO);
}

VBOProxy::~VBOProxy() = default;
/**
 *@author: baizf
 *@date: 2022/12/14
*/
//

#include "EBOProxy.h"
#include "ErrorProxy.h"

EBOProxy::EBOProxy(const void *indices, unsigned int size) {
    glGenBuffers(1, &mEBO);

    //该方法必须在glBindVertexArray方法(绑定VAO)之后(解绑VAO之前)调用
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, //目标缓冲的类型：顶点缓冲对象当前绑定到GL_ELEMENT_ARRAY_BUFFER目标上
                 sizeof(unsigned int) * size, //指定传输数据的大小(以字节为单位)
                 indices, //实际数据
                 GL_STATIC_DRAW); //指定了我们希望显卡如何管理给定的数据, GL_STATIC_DRAW: 数据不会或几乎不会改变。

    ErrorProxy::checkError("glBufferData mEBO");
}

void EBOProxy::destroy() {
    glDeleteBuffers(1, &mEBO);
}

EBOProxy::~EBOProxy() = default;
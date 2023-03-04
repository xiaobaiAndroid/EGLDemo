/**
 *@author: baizf
 *@date: 2022/12/3
*/
//

#include "VAOProxy.h"
#include "ErrorProxy.h"
#include "Logutils.h"

VAOProxy::VAOProxy() {
    glGenVertexArrays(1, &mVAO);

}

void VAOProxy::bind() const {
    glBindVertexArray(mVAO);
}

void
VAOProxy::parseVertices(const int index, const GLint size, const int stride, const int offset) {

    glVertexAttribPointer(index, //指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
                          size, //顶点属性的大小。假如顶点属性是一个vec3，它由3个值组成，所以大小是3
                          GL_FLOAT, //数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
                          GL_FALSE, //希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE
                          stride * sizeof(float), //步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。以字节为单位
                          (void *)(offset * sizeof(float)));//位置数据在缓冲中起始位置的偏移量(Offset),以字节为单位
    glEnableVertexAttribArray(index);

    string message = "parseVertices: index=" + to_string(index) + ", offset=" + to_string(offset);
    LOGI("%s", message.c_str());

    ErrorProxy::checkError(message);

}

void VAOProxy::unbind() const{
    glBindVertexArray(GL_NONE);
}


void VAOProxy::destroy() {
    glDeleteVertexArrays(1, &mVAO);
    mVAO = 0;
}

VAOProxy::~VAOProxy() = default;
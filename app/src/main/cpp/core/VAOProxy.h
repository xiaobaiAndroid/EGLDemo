/**
 *@author: baizf
 *@date: 2022/12/3
*/
//

#ifndef OPENGLDEMO_VAOPROXY_H
#define OPENGLDEMO_VAOPROXY_H

#include <GLES3/gl31.h>

class VAOProxy{
private:
    GLuint mVAO = 0;
public:

    VAOProxy();

    /* 告诉OpenGL如何解析当前绑定的VAO数据
     *  index: 顶点属性的位置值（顶点着色器中的layout(location = index)）
     *   stride: 步长
     *   offset：数据开始位置的偏移量, 单位：字节
     *   size: 顶点数据的长度 vec3类型长度就是3 vec2长度就2
     * */
    void parseVertices(const int index, const GLint size, const int stride, const int offset);
    //绘制前或者设置参数前，需要绑定VAO
    void bind() const;

    void unbind() const;
    void destroy();

    ~VAOProxy();
};

#endif //OPENGLDEMO_VAOPROXY_H

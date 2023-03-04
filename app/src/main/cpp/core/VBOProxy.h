/**
 * VBO代理类
 *@author: baizf
 *@date: 2022/12/3
*/
//

#ifndef OPENGLDEMO_VBOPROXY_H
#define OPENGLDEMO_VBOPROXY_H

#include <GLES3/gl31.h>

class VBOProxy{
private:
    GLuint mVBO;
public:

    VBOProxy(const void *vertices, const unsigned int arrSize);

    void destroy();
    //绑定后，VAO使用的是该VBO缓存的数据
    void bind();
    ~VBOProxy();

};

#endif //OPENGLDEMO_VBOPROXY_H

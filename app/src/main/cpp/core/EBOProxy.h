/**
 * 元素缓冲对象(Element Buffer Object，EBO)，也叫索引缓冲对象(Index Buffer Object，IBO)
 *@author: baizf
 *@date: 2022/12/14
*/
//

#ifndef OPENGLDEMO_EBOPROXY_H
#define OPENGLDEMO_EBOPROXY_H

#include <GLES3/gl31.h>

class EBOProxy{
private:
    GLuint mEBO;
public:
    //size: indices数组的大小
    EBOProxy(const void *indices, unsigned int  size);

    void destroy();
    ~EBOProxy();

};

#endif //OPENGLDEMO_EBOPROXY_H

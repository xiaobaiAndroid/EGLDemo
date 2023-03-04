/**
 *
 *@author: baizf
 *@date: 2022/12/3
*/
//

#ifndef OPENGLDEMO_TEXTUREPROXY_H
#define OPENGLDEMO_TEXTUREPROXY_H

#include "NativeImage.h"
#include <string>
#include "ShaderProxy.h"

using namespace std;

class TextureProxy {
private:
    GLuint mTexture = 0;

    //纹理单元
    GLenum mUnit = GL_TEXTURE0;

public:
    TextureProxy(GLenum unit = GL_TEXTURE0);

    void setImage2D(NativeImage *image, int wrap_s_param = GL_CLAMP_TO_EDGE,
                    int wrap_t_param = GL_CLAMP_TO_EDGE, int mag_filter_param = GL_LINEAR,
                    int min_filter_param = GL_LINEAR, bool isGenerateMipmap = false) const;

    void setSRGBImage2D(NativeImage *image, GLint format = GL_SRGB8_ALPHA8,int wrap_s_param = GL_CLAMP_TO_EDGE,
                    int wrap_t_param = GL_CLAMP_TO_EDGE, int mag_filter_param = GL_LINEAR,
                    int min_filter_param = GL_LINEAR, bool isGenerateMipmap = false) const;

    //调用glDraw方法前调用
    void bind() const;
    void unbind() const;

    void destroy();

    //获取纹理单元对应的位置值
    int getTextureUnitPos() const;

    //把纹理单元mUnit中的纹理数据映射(关联)到片段着色器名为uniformName(sampler2D类型)变量中
    void mapToFragShader(GLuint program, string &uniformName);

    GLuint getId();

    ~TextureProxy();

    void modifyImage2D(NativeImage *image);
};

#endif //OPENGLDEMO_TEXTUREPROXY_H

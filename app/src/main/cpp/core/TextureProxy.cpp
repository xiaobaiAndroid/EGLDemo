/**
 * 纹理代理类
 *@author: baizf
 *@date: 2022/12/3
*/
//

#include <android/bitmap.h>
#include "TextureProxy.h"
#include "Logutils.h"


TextureProxy::TextureProxy(GLenum unit) {
    glGenTextures(1, &mTexture);
    mUnit = unit;

}


void
TextureProxy::setImage2D(NativeImage *image, int wrap_s_param, int wrap_t_param,
                         int mag_filter_param,
                         int min_filter_param, bool isGenerateMipmap) const {
    if (!image) {
        return;
    }
    int format;
    if (image->format == AndroidBitmapFormat::ANDROID_BITMAP_FORMAT_RGB_565) {
        format = GL_RGB565;
    } else if (image->format == ANDROID_BITMAP_FORMAT_RGBA_4444) {
        format = GL_RGBA4;
    }
    {
        format = GL_RGBA;
    }

    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_param);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter_param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter_param);

    glTexImage2D(GL_TEXTURE_2D, 0, format, image->width, image->height, 0, format,
                 GL_UNSIGNED_BYTE, image->data);
    if (isGenerateMipmap) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}


void TextureProxy::modifyImage2D(NativeImage *image) {
    if (!image) {
        return;
    }
    int format;
    if (image->format == AndroidBitmapFormat::ANDROID_BITMAP_FORMAT_RGB_565) {
        format = GL_RGB565;
    } else if (image->format == ANDROID_BITMAP_FORMAT_RGBA_4444) {
        format = GL_RGBA4;
    }else{
        format = GL_RGBA;
    }

    bind();
    //修改图像函数，因为修改一个纹理比重新创建一个纹理开销小得多
    // xoffset,yoffset是要修改的图像的左下角偏移
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->width, image->height, format, GL_UNSIGNED_BYTE,
                    image->data);

}


void
TextureProxy::setSRGBImage2D(NativeImage *image, GLint format, int wrap_s_param, int wrap_t_param,
                             int mag_filter_param, int min_filter_param,
                             bool isGenerateMipmap) const {
    if (!image) {
        return;
    }
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_param);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter_param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter_param);

    glTexImage2D(GL_TEXTURE_2D, 0, format, image->width, image->height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image->data);
    if (isGenerateMipmap) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

}


void TextureProxy::bind() const {
    //给纹理采样器分配一个位置值，这样的话我们能够在一个片段着色器中设置多个纹理。一个纹理的位置值通常称为一个纹理单元(Texture Unit)。
    // 一个纹理的默认纹理单元是0，它是默认的激活纹理单元
    //一个片段着色器右多个sampler2D时需要激活不同的纹理单元
    glActiveTexture(mUnit);
    glBindTexture(GL_TEXTURE_2D, mTexture);
}


void TextureProxy::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

int TextureProxy::getTextureUnitPos() const {
    int pos = 0;
    if (mUnit == GL_TEXTURE0) {
        pos = 0;
    } else if (mUnit == GL_TEXTURE1) {
        pos = 1;
    } else if (mUnit == GL_TEXTURE2) {
        pos = 2;
    } else if (mUnit == GL_TEXTURE3) {
        pos = 3;
    } else if (mUnit == GL_TEXTURE4) {
        pos = 4;
    } else if (mUnit == GL_TEXTURE5) {
        pos = 5;
    } else if (mUnit == GL_TEXTURE6) {
        pos = 6;
    } else if (mUnit == GL_TEXTURE7) {
        pos = 7;
    } else if (mUnit == GL_TEXTURE8) {
        pos = 8;
    } else if (mUnit == GL_TEXTURE9) {
        pos = 9;
    } else if (mUnit == GL_TEXTURE10) {
        pos = 10;
    } else if (mUnit == GL_TEXTURE11) {
        pos = 11;
    } else if (mUnit == GL_TEXTURE12) {
        pos = 12;
    } else if (mUnit == GL_TEXTURE13) {
        pos = 13;
    } else if (mUnit == GL_TEXTURE14) {
        pos = 14;
    } else if (mUnit == GL_TEXTURE15) {
        pos = 15;
    }
    return pos;
}

void TextureProxy::mapToFragShader(GLuint program, string &uniformName) {
    bind();
    ShaderProxy::setInt(program, uniformName, getTextureUnitPos());
}

TextureProxy::~TextureProxy() = default;

GLuint TextureProxy::getId() {
    return mTexture;
}

void TextureProxy::destroy() {
    glDeleteTextures(1, &mTexture);
}


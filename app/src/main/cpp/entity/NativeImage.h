//
// Created by BZF on 2022/2/16.
//

#ifndef OPENGLESDEMO_IMAGE_H
#define OPENGLESDEMO_IMAGE_H

#include <stdint.h>

struct NativeImage{
    int width = 0;
    int height = 0;
    unsigned char *data = nullptr;
    //图片格式 参考 AndroidBitmapFormat
    int32_t format = 0;

};

#endif //OPENGLESDEMO_IMAGE_H

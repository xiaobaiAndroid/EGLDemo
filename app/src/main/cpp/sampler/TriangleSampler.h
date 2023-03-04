/**
 *@author: baizf
 *@date: 2023/2/24
*/
//

#ifndef EGLSAMPLE_TRIANGLESAMPLER_H
#define EGLSAMPLE_TRIANGLESAMPLER_H

#include "CoreProxy.h"


static string vertSrc = "#version 310 es\n"
                        "\n"
                        "layout(location = 0) in vec3 aPos;\n"
                        "\n"
                        "void main(){\n"
                        "    gl_Position = vec4(aPos, 1.0f);\n"
                        "}";

static string fragSrc = "#version 310 es\n"
                        "precision mediump float;\n"
                        "\n"
                        "out vec4 FragColor;\n"
                        "\n"
                        "void main(){\n"
                        "    FragColor = vec4(1.0f, 0.0f,0.0f,1.0f);\n"
                        "}";

class TriangleSampler{
private:
    ProgramProxy *mProgramProxy = nullptr;
    VBOProxy *mVBO = nullptr;
    VAOProxy *mVAO = nullptr;
public:
    TriangleSampler();
    ~TriangleSampler();

    void draw();
};

#endif //EGLSAMPLE_TRIANGLESAMPLER_H

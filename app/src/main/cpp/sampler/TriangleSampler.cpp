/**
 *@author: baizf
 *@date: 2023/2/24
*/
//

#include "TriangleSampler.h"


TriangleSampler::TriangleSampler() {
    mProgramProxy = new ProgramProxy(vertSrc, fragSrc);

    float vertices[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f
    };
    mVBO = new VBOProxy(vertices,9);
    mVAO = new VAOProxy();
    mVAO->bind();
    mVAO->parseVertices(0,3,3,0);
    mVAO->unbind();
}

TriangleSampler::~TriangleSampler() {
    mProgramProxy->destroy();
    delete mProgramProxy;

    mVBO->destroy();
    delete mVBO;

    mVAO->destroy();
    delete mVAO;
}

void TriangleSampler::draw() {
    ProgramProxy::clearColor();

    mProgramProxy->use();

    mVAO->bind();
    glDrawArrays(GL_TRIANGLES,0,3);
    mVAO->unbind();
}
/**
 *@author: baizf
 *@date: 2022/12/3
*/
//

#include "CoordinateSystems.h"
#include "ShaderProxy.h"
#include <GLES3/gl31.h>

glm::mat4
CoordinateSystems::createPerspectiveProjection(float ratioWH, float fov, float near, float far) {
    return glm::perspective(glm::radians(fov), ratioWH, near, far);
}

glm::mat4 CoordinateSystems::createOrthoProjection(float left, float right, float top, float bottom,
                                                   float near, float far) {
    return glm::ortho(left,right,bottom,top, near, far);
}

glm::mat4 CoordinateSystems::createView(CameraProxy *cameraProxy) {
    return glm::lookAt(cameraProxy->mPosition, cameraProxy->mPosition + cameraProxy->mFront,
                       cameraProxy->mUp);
}


glm::mat4
CoordinateSystems::createModel(ModelMatrix &modelMatrix) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, modelMatrix.translate);
    model = glm::scale(model, modelMatrix.scale);
    if (modelMatrix.angleX != 0.0f) {
        model = glm::rotate(model, glm::radians(modelMatrix.angleX), glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (modelMatrix.angleY != 0.0f) {
        model = glm::rotate(model, glm::radians(modelMatrix.angleY),glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (modelMatrix.angleZ != 0.0f) {
        model = glm::rotate(model, glm::radians(modelMatrix.angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
    }
    return model;
}

void CoordinateSystems::setViewport(const int width, const int height, const int leftBottomX,
                                    const int leftBottomY) {
    glViewport(leftBottomX, leftBottomY, width, height);
}

void CoordinateSystems::setMatrixToShader(GLuint program, const string &shaderName, glm::mat4 &data) {
    ShaderProxy::setMat4(program, shaderName, data);
}
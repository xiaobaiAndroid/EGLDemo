/**
 *@author: baizf
 *@date: 2022/12/3
*/
//

#include "CameraProxy.h"
#include "../include/glm/gtc/matrix_transform.hpp"


CameraProxy::CameraProxy(glm::vec3 position, glm::vec3 worldUp, float yaw,
                         float pitch) : mFront(0.0f, 0.0f, -1.0f), mRight() {

    mPosition = position;
    mWorldUp = worldUp;
    mYaw = yaw;
    mPitch = pitch;
    coordinate2DTo3D();

}

void CameraProxy::coordinate2DTo3D() {
    glm::vec3 front;
    front.x = cos(glm::radians(mPitch)) * cos(glm::radians(mYaw));
    front.y = sin(glm::radians(mPitch));
    front.z = cos(glm::radians(mPitch)) * sin(glm::radians(mYaw));
    mFront = glm::normalize(front);

    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUp = glm::normalize(glm::cross(mRight, mFront));

}


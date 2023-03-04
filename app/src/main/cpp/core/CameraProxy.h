/**
 * 摄像机
 *@author: baizf
 *@date: 2022/12/3
*/
//

#ifndef OPENGLDEMO_CAMERAPROXY_H
#define OPENGLDEMO_CAMERAPROXY_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float YAW         = -90.0f;
const float PITCH       =  0.0f;

class CameraProxy {
private:
    void coordinate2DTo3D();
public:
    //摄像机位置
    glm::vec3 mPosition;
    ////摄像机上轴(世界坐标，2D空间)
    glm::vec3 mWorldUp;

    //方向向量(欧拉角,即3D空间)
    glm::vec3 mFront;
    //摄像机上轴(3D空间)
    glm::vec3 mUp;
    //摄像机右向量(3D空间)
    glm::vec3 mRight;

    //欧拉角:  偏航角 偏航初始化为-90.0度，因为偏航0.0会导致方向向量指向右边，所以我们最初向左旋转了一点。
    float mYaw;
    //欧拉角：俯仰角  一般设置在 -90°~90°之间
    float mPitch;

    CameraProxy(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
                glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),  float yaw = YAW, float pitch = PITCH);

};

#endif //OPENGLDEMO_CAMERAPROXY_H

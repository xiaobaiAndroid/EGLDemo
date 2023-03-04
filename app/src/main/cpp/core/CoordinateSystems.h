/**
 *
 * 坐标系统：顶点在最终转化为屏幕坐标之前还会被变换到多个坐标系统。
 * 局部空间->世界空间->观察空间->裁剪空间->屏幕空间
 *@author: baizf
 *@date: 2022/12/3
*/

#ifndef OPENGLDEMO_COORDINATESYSTEMS_H
#define OPENGLDEMO_COORDINATESYSTEMS_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLES3/gl31.h>
#include "CameraProxy.h"
#include <string>
#include <vector>

using namespace std;


struct ModelMatrix{
public:
    glm::vec3 translate = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    //x,y,z轴旋转角度
    float angleX = 0.0f;
    float angleY = 0.0f;
    float angleZ = 0.0f;

};

class CoordinateSystems{
private:
public:

    /*
     * 创建一个透视投影矩阵。 把观察空间坐标转换成裁剪空间坐标
     * 将顶点坐标从观察变换到裁剪空间需要一个投影矩阵
     * fov: 视野，通常设置为45.0
     * ratioWH: 宽高比，由视口的宽除以高
     * near: 近平面 通常为0.1
     * far: 远平面 通常为100.0
     * */
    static glm::mat4 createPerspectiveProjection(float ratioWH, float fov = 45.0f, float near = 0.1f, float far = 100.f);


    /*
 *创建一个正交投影矩阵，把观察空间坐标转换成裁剪空间坐标
 * left：指定了平截头体的左坐标, 值的范围 -1.0~0.0
 * right: 右坐标：值范围：0.0~1.0
 *  bottom：指定了平截头体的底部 值的范围：-1.0~0.0
 *  top: 指定了平截头体的顶部 值范围：0.0~1.0
 * */
    static glm::mat4 createOrthoProjection(float left, float right,float top,float bottom, float near = 0.1f, float far = 100.f);

    /*
     * 创建一个观察矩阵。 从局部坐标转换世界坐标
     * */
    static glm::mat4 createView(CameraProxy *cameraProxy);


    /*
    * 创建一个模型矩阵。  把世界空间的坐标转换成观察空间的坐标
     *
    * */
    static glm::mat4 createModel(ModelMatrix &modelMatrix);

    /*
     * 视口变换。裁剪坐标变换为屏幕坐标。
     * 视口变换将位于-1.0到1.0范围的坐标变换到由glViewport函数所定义的坐标范围内。最后变换出来的坐标将会送到光栅器，将其转化为片段。
     * */
    static void setViewport(const int width, const int height, const int leftBottomX = 0, const int leftBottomY = 0);


    /*
     * 设置(投影，观察，模型)矩阵到着色器
     * shaderName: 片段着色器对应的变量名
     * */
    static void setMatrixToShader(GLuint program, const string &shaderName, glm::mat4 &data);
};

#endif //OPENGLDEMO_COORDINATESYSTEMS_H

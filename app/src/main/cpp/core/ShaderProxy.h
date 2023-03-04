/**
 * 着色器：顶点着色器和片段着色器
 *@author: baizf
 *@date: 2022/12/3
*/
//

#ifndef OPENGLDEMO_SHADERPROXY_H
#define OPENGLDEMO_SHADERPROXY_H

#include <GLES3/gl31.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

using namespace std;

class ShaderProxy{
public:
    //设置着色器程序中的mat4矩阵
    static void setMat4(GLuint program, const string &name, glm::mat4 &data);

    static void setVec3(GLuint program, const string &name, glm::vec3 &data);
    static void setVec2(GLuint program, const string &name, glm::vec2 &data);
    static void setFloat(GLuint program, const string &name, float data);
    static void setInt(GLuint program, const string &name, int data);
};

#endif //OPENGLDEMO_SHADERPROXY_H

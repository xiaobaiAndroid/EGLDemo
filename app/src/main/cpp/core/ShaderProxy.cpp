/**
 *@author: baizf
 *@date: 2022/12/3
*/
//

#include "ShaderProxy.h"
#include "ErrorProxy.h"

#include <glm/gtc/type_ptr.hpp>

void ShaderProxy::setMat4(GLuint program,const string &name, glm::mat4 &data) {
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(data));
    ErrorProxy::checkError();
}

void ShaderProxy::setVec3(GLuint program, const string &name, glm::vec3 &data) {
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, glm::value_ptr(data));
    ErrorProxy::checkError();
}

void ShaderProxy::setVec2(GLuint program, const string &name, glm::vec2 &data) {
    glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, glm::value_ptr(data));
    ErrorProxy::checkError();
}

void ShaderProxy::setFloat(GLuint program, const string &name, float data) {
    glUniform1f(glGetUniformLocation(program,name.c_str()), data);
    ErrorProxy::checkError();
}

void ShaderProxy::setInt(GLuint program, const string &name, int data) {
    glUniform1i(glGetUniformLocation(program, name.c_str()), data);
    ErrorProxy::checkError();
}
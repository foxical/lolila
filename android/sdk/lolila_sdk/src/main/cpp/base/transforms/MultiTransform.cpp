//
// Created by tam on 2021/7/27.
//
#include "MultiTransform.h"

void MultiTransform::scale(const glm::vec3& v){
    M = glm::scale(M,v);
}
void MultiTransform::rotate(const float angle, const glm::vec3& axis){
    M = glm::rotate(M,glm::radians(angle),axis);
}
void MultiTransform::translate(const glm::vec3& v){
    M = glm::translate(M,v);
}

Vector MultiTransform::doTransform(const glm::mat4& mat4,const Vector& t){
    const glm::vec4 v1(t.x(),t.y(),t.z(),1.0f);
    glm::vec4 v2 = mat4*v1;
    return Vector(v2.x,v2.y,v2.z);
}

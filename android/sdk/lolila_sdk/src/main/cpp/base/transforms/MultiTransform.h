//
// Created by tam on 2021/7/27.
//

#ifndef _MULTITRANSFORM_H
#define _MULTITRANSFORM_H

// Include all GLM core / GLSL features
#include <glm/glm.hpp> // vec2, vec3, mat4, radians
// Include all GLM extensions
#include <glm/ext.hpp> // perspective, translate, rotate
#include "../geometry/Vector.h"


class MultiTransform{
public:
    MultiTransform():M(glm::mat4(1.f)){

    }
    ~MultiTransform(){

    }

    void scale(const glm::vec3& );
    void rotate(const float angle, const glm::vec3&);
    void translate(const glm::vec3&);

    const glm::mat<4,4,float>& getMat()const{
        return M;
    }

    static Vector doTransform(const glm::mat4&,const Vector&);

private:
   glm::mat4 M;
};

#endif //_MULTITRANSFORM_H

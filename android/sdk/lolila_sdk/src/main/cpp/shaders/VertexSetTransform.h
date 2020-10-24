//
// Created by tam on 2020/10/16.
//

#ifndef _VERTEXSETTRANSFORM_H
#define _VERTEXSETTRANSFORM_H

#include <GLES3/gl3.h>

class Matrix;
class SimpleVertexSet;

class VertexSetTransform {
public:

    static void positionTransformByMat(SimpleVertexSet& vs, const Matrix& m);

    /**
     *
     * @param angleStrider
     * 每个顶点跨越多少度
     * 例如半圆总共共180度，如果一个顶点跨越3度，则共有180/3 = 60 + 1 = 61个顶点
     * @return
     */
    static int semiCircleCount(float angleStrider);

    static int circleCount(float angleStrider);

    /**
     * 设置圆顶点
     * @param vs
     * @param angleStrider
     * @param radius
     */
    static void setCirclePos(SimpleVertexSet& vs,float angleStrider, GLfloat radius);

private:

};


#endif //_VERTEXSETTRANSFORM_H

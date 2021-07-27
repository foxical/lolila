//
// Created by tam on 2021/7/2.
//
#include "LinearlyIndependent.h"
#include "../geometry/Vector.h"
#include "../math/Matrix.h"
#include <stdexcept>

/**
 *
 * @param v1
 * @param v2
 * @return
 */
bool LinearlyIndependent::check2(const Vector& v1,const Vector& v2){
    if (v1.dim() != v2.dim()) {
        throw runtime_error("Dim A not equal with B!");
    }



    if(v1.dim()==2) {


        Matrix m(2, 2);
        m.set(0, 0, v1.x());
        m.set(1, 0, v1.y());
        m.set(0, 1, v2.x());
        m.set(1, 1, v2.y());
        return m.isInvertible();
    }

    if( v1.dim()==3){
        Matrix m(3, 3);
        m.set(0, 0, v1.x());
        m.set(1, 0, v1.y());
        m.set(2, 0, v1.z());
        m.set(0, 1, v2.x());
        m.set(1, 1, v2.y());
        m.set(2, 1, v2.z());

        Vector v3 = Vector::cross(v1,v2);
        m.set(0, 2, v3.x());
        m.set(1, 2, v3.y());
        m.set(2, 2, v3.z());

        return m.isInvertible();
    }

    return false;
}

bool LinearlyIndependent::check3(const Vector& v1,const Vector& v2,const Vector& v3) {
    if(v1.dim()!=3){
        throw  runtime_error("Dim 1 must be 3!");
    }
    if(v2.dim()!=3){
        throw  runtime_error("Dim 2 must be 3!");
    }
    if(v3.dim()!=3){
        throw  runtime_error("Dim 3 must be 3!");
    }

    Matrix m(3,3);
    m.set(0,0,v1.x());
    m.set(1,0,v1.y());
    m.set(2,0,v1.z());
    m.set(0,1,v2.x());
    m.set(1,1,v2.y());
    m.set(2,1,v2.z());
    m.set(0,2,v3.x());
    m.set(1,2,v3.y());
    m.set(2,2,v3.z());
    return m.isInvertible();

}



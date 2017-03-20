//
// Created by tam on 2017/1/21.
//
#include "Vector.h"
#include <math.h>

Vector::Vector(const float &x, const float &y) {
    _dim= 2;
    _components[0] = x;
    _components[1] = y;
}

Vector::Vector(const float &x, const float &y, const float &z) {
    _dim=3;
    _components[0] = x;
    _components[1] = y;
    _components[2] = z;
}

Vector::Vector(const Vector& generalVector) {
    this->_dim= generalVector._dim;
    for(int d=0;d<_dim;++d){
        this->_components[d]=generalVector._components[d];
    }
}

Vector::~Vector() {

}

const float Vector::x() const {
    return _components[0];
}

const float Vector::y() const {
    return _components[1];
}

const float Vector::z() const {
    return _components[2];
}

const float Vector::length() const {
    float result=0;
    for(int d=0;d<_dim;++d){
        result += powf(_components[d],2.0);
    }
    return sqrtf(result);
}

const float Vector::dot(const Vector& a, const Vector& b){
    float  result=0;
    for( int d=0;d<a._dim;++d){
        result += a._components[d] * b._components[d];
    }
    return result;
}

const float Vector::dot(const Vector& a) const{
     return dot(*this,a);
}


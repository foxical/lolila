//
// Created by tam on 2017/1/21.
//
#include "Vector.h"
#include <math.h>
#include <stdexcept>


Vector::Vector(const float &x) {
    _dim= 1;
    _components[0] = x;
}

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

float Vector::x() const {
    return _components[0];
}

float Vector::y() const {
    if( _dim<2){
        throw runtime_error("Vector must has 2 dims!");
    }
    return _components[1];
}

float Vector::z() const {
    if( _dim<3){
        throw runtime_error("Vector must has 3 dims!");
    }
    return _components[2];
}

float Vector::length() const {
    float result=0;
    for(int d=0;d<_dim;++d){
        result += powf(_components[d],2.0);
    }
    return sqrtf(result);
}

float Vector::dot(const Vector& a, const Vector& b){
    if( a._dim != b._dim){
        throw  runtime_error("Dim A not equal with B!");
    }
    float  result=0;
    for( int d=0;d<a._dim;++d){
        result += a._components[d] * b._components[d];
    }
    return result;
}

float Vector::dot(const Vector& a) const{
     return dot(*this,a);
}

int Vector::dim()const{
    return _dim;
}

Vector Vector::cross(const Vector& A,const Vector& B){
    if( A._dim!=3){
        throw runtime_error("Vector A must has 3 dim!");
    }
    if( B._dim!=3){
        throw runtime_error("Vector B must has 3 dim!");
    }
    //a × b = [AyBz − AzBy, AzBx − AxBz, AxBy − AyBx]
    return Vector(A.y()*B.z()-A.z()*B.y(), A.z()*B.x()-A.x()*B.z(),A.x()*B.y()-A.y()*B.x());
}

Vector Vector::cross(const Vector& a)const {
    return cross(*this,a);
}

string Vector::toString() const {
    char buff[128];
    string result;
    result.append("<");
    if( _dim>0){
        sprintf(buff,"%g",_components[0]);
        result.append(buff);
        for( int d=1;d<_dim;++d){
            result.append(",");
            sprintf(buff,"%g",_components[d]);
            result.append(buff);
        }
    }
    result.append(">");
    return result;
}

const char* Vector::c_str() const {
    return toString().c_str();
}

Vector Vector::scalarMultiply( const Vector& a,const float& val){
    Vector result(a);
    for(int d=0;d<a._dim;++d){
        result._components[d] = a._components[d]*val;
    }
    return result;
}

Vector Vector::scalarMultiply(const float &val)const{
    return scalarMultiply(*this,val);
}

Vector Vector::proj(const Vector& P,const Vector& Q){
    return scalarMultiply(Q,dot(P,Q)/powf(Q.length(),2.0));
}

Vector Vector::proj(const Vector& Q)const{
    return proj(*this,Q);
}

Vector Vector::add(const Vector& a,const Vector& b){
    if( a._dim != b._dim){
        throw  runtime_error("Dim A not equal with B!");
    }
    Vector result(a);
    for(int d=0;d<a._dim;++d){
        result._components[d] = a._components[d] + b._components[d];
    }
    return result;
}

Vector Vector::minus(const Vector& a,const Vector& b){
    if( a._dim != b._dim){
        throw  runtime_error("Dim A not equal with B!");
    }
    const Vector fb = Vector::scalarMultiply(b,-1.0);
    return add(a,fb);
}

Vector Vector::add(const Vector& a)const{
    return add(*this,a);
}

Vector Vector::minus(const Vector& a)const{
    return minus(*this,a);
}

Vector Vector::perp(const Vector& P,const Vector& Q){
    return minus(P,proj(P,Q));
}

Vector Vector::perp(const Vector& Q)const{
    return perp(*this,Q);
}

Vector Vector::normalize(const Vector& a){
    return scalarMultiply(a, 1/a.length());
}

Vector Vector::normalize()const{
    return normalize(*this);
}

Vector& Vector::operator=(const Vector& a){
    _dim = a._dim;
    for(int d=0;d<_dim;++d){
        _components[d]=a._components[d];
    }
    return *this;
}

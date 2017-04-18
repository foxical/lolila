//
// Created by Administrator on 2017/4/18.
//

#include "HomogeneousCoordinate.h"

HomogeneousCoordinate::HomogeneousCoordinate(const float& x,const float& w):_vector(x),_w(w){

}
HomogeneousCoordinate::HomogeneousCoordinate(const float& x,const float& y,const float& w):_vector(x,y),_w(w){

}
HomogeneousCoordinate::HomogeneousCoordinate(const float& x,const float& y,const float& z,const float& w):_vector(x,y,z),_w(w){

}
HomogeneousCoordinate::HomogeneousCoordinate(const Vector& ref,const float& w):_vector(ref),_w(w){

}
HomogeneousCoordinate::HomogeneousCoordinate(const HomogeneousCoordinate& hc):_vector(hc._vector),_w(hc._w){

}

int HomogeneousCoordinate::dot(const HomogeneousCoordinate& hc1, const HomogeneousCoordinate& hc2) {
    return Vector::dot(hc1._vector,hc2._vector) + (hc1._w*hc2._w);
}

int HomogeneousCoordinate::dot(const HomogeneousCoordinate& hc)const{
    return dot(*this,hc);
}
//
// Created by Administrator on 2017/4/18.
//

#include "HomogeneousCoordinate.h"

HomogeneousCoordinate::HomogeneousCoordinate(const double& x,const double& w):_vector(x),_w(w){

}
HomogeneousCoordinate::HomogeneousCoordinate(const double& x,const double& y,const double& w):_vector(x,y),_w(w){

}
HomogeneousCoordinate::HomogeneousCoordinate(const double& x,const double& y,const double& z,const double& w):_vector(x,y,z),_w(w){

}
HomogeneousCoordinate::HomogeneousCoordinate(const Vector& ref,const double& w):_vector(ref),_w(w){

}
HomogeneousCoordinate::HomogeneousCoordinate(const HomogeneousCoordinate& hc):_vector(hc._vector),_w(hc._w){

}

double HomogeneousCoordinate::dot(const HomogeneousCoordinate& hc1, const HomogeneousCoordinate& hc2) {
    return Vector::dot(hc1._vector,hc2._vector) + (hc1._w*hc2._w);
}

double HomogeneousCoordinate::dot(const HomogeneousCoordinate& hc)const{
    return dot(*this,hc);
}
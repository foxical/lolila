//
// Created by tam on 2017/1/21.
//

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <string>
using namespace std;

class Vector{

public:
    Vector(const double& x);
    Vector(const double& x,const double& y);
    Vector(const double& x,const double& y,const double& z);
    Vector(const Vector&);
    ~Vector();

public:

    double x()const;
    double y()const;
    double z()const;
    double length()const;
    double dot(const Vector&)const;
    Vector cross(const Vector&)const;
    Vector scalarMultiply(const double &)const;
    Vector proj(const Vector&)const;
    Vector perp(const Vector&)const;
    Vector add(const Vector&)const;
    Vector minus(const Vector&)const;
    Vector normalize()const;
    int dim()const;
    bool isZero()const;

public:

    string toString()const;
    const char* c_str()const;
public:
    Vector& operator=(const Vector&);

public:

    static double dot(const Vector&, const Vector&);
    static Vector cross(const Vector&,const Vector&);
    static Vector scalarMultiply( const Vector&,const double&);
    static Vector proj(const Vector& P,const Vector& Q);
    static Vector perp(const Vector& P,const Vector& Q);
    static Vector add(const Vector&,const Vector&);
    static Vector minus(const Vector&,const Vector&);
    static Vector normalize(const Vector&);

private:
    Vector();

private:
    double _components[3];
    int _dim;

};


#endif //__VECTOR_H__

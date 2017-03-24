//
// Created by tam on 2017/1/21.
//

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <string>
using namespace std;

class Vector{

public:
    Vector(const float& x);
    Vector(const float& x,const float& y);
    Vector(const float& x,const float& y,const float& z);
    Vector(const Vector&);
    ~Vector();

public:

    float x()const;
    float y()const;
    float z()const;
    float length()const;
    float dot(const Vector&)const;
    Vector cross(const Vector&)const;
    Vector multiply( const float&)const;
    Vector proj(const Vector&)const;
    Vector perp(const Vector&)const;
    Vector add(const Vector&)const;
    Vector minus(const Vector&)const;
    Vector normalize()const;
    int dim()const;

public:

    string toString()const;
public:
    Vector& operator=(const Vector&);

public:

    static float dot(const Vector&, const Vector&);
    static Vector cross(const Vector&,const Vector&);
    static Vector multiply( const Vector&,const float&);
    static Vector proj(const Vector& P,const Vector& Q);
    static Vector perp(const Vector& P,const Vector& Q);
    static Vector add(const Vector&,const Vector&);
    static Vector minus(const Vector&,const Vector&);
    static Vector normalize(const Vector&);

private:
    Vector();

private:
    float _components[3];
    int _dim;

};


#endif //__VECTOR_H__

//
// Created by tam on 2017/1/21.
//

#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector{

public:
    Vector(const float& x,const float& y);
    Vector(const float& x,const float& y,const float& z);
    Vector(const Vector&);
    ~Vector();

public:

    const float x()const;
    const float y()const;
    const float z()const;
    const float length()const;
    const float dot(const Vector&)const;

public:

    static const float dot(const Vector&, const Vector&);

private:
    Vector();

private:
    float _components[3];
    int _dim;

};


#endif //__VECTOR_H__

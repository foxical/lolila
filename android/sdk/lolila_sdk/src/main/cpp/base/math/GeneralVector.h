//
// Created by tam on 2017/1/21.
//

#ifndef _GENERAL_VECTOR_H
#define _GENERAL_VECTOR_H

class GeneralVector{

public:

    GeneralVector(const float& x,const float& y,const float& z);
    GeneralVector(const GeneralVector&);
    ~GeneralVector();

public:

    const float x()const;
    const float y()const;
    const float z()const;
    const float length()const;

public:

    GeneralVector dot(const GeneralVector&)const;



private:
    float * _components;
    int _dim;

};


#endif //_GENERAL_VECTOR_H

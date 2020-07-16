//
// Created by tam on 2020/7/16.
//

#ifndef __FRACTIONOUTPUTADAPTER_HPP__
#define __FRACTIONOUTPUTADAPTER_HPP__

#ifndef __FRACTION_H__
#include "Fraction.h"
#endif

#include <string>
using namespace std;

struct FractionOutputAdapter{

    static string toString(const Fraction& f ){
        if(f.getNumerator()==0L){
            return string("0");
        }else{
            Fraction clone(f);
            clone.reduce();
            return (string)clone;
        }
    }
};

#endif //_FRACTIONOUTPUTADAPTER_HPP

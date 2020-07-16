//
// Created by tam on 2020/7/16.
//

#ifndef __FLOATOUTPUTADAPTER_HPP__
#define __FLOATOUTPUTADAPTER_HPP__

#include <string>
#include <sstream>
using namespace std;

struct FloatOutputAdapter{

    static string toString(const float& f ){
        std::stringstream output;
        output<<f;
        return output.str();
    }
};


#endif //DEMO_FLOATOUTPUTADAPTER_HPP

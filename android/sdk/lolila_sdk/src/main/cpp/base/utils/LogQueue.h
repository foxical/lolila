//
// Created by Administrator on 2017/4/6.
//

#ifndef __LOGQUEUE_H__
#define __LOGQUEUE_H__

#include <string>
using namespace std;

class LogQueue{
public :
    static void push(const char* __restrict, ...);
    static void push(const string& s){
        s_log_str.append(s);
    }
    static const char* c_str(){
        return s_log_str.c_str();
    }
    static void clear(){
        s_log_str.clear();
    }
private:
    LogQueue();
    ~LogQueue();
private:
    static string s_log_str;
};

#endif //__LOGQUEUE_H__

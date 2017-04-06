//
// Created by Administrator on 2017/4/6.
//

#include "LogQueue.h"

string LogQueue::s_log_str = "";

void LogQueue::push(const char* format, ...){

    char buf[1024];
    va_list st;
    va_start(st, format);
    vsprintf(buf,format, st);
    va_end(st);

    s_log_str.append(buf);
}

#ifndef TEST_OFFSETINFO_H
#define TEST_OFFSETINFO_H

#include <string>
#include "Register.h"

using namespace std;

struct OffsetInfo{
    set<string>::iterator src_path;
    int src_line;
    set<string>::iterator code;
    Register reg_gpr;


    //vector<Register> vec_reg;   //存储寄存器状态
};

#endif //TEST_OFFSETINFO_H

//
// Created by Minghao Guo on 2022/5/14.
//

#ifndef TEST_FUNCINFO_H
#define TEST_FUNCINFO_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include "OffsetInfo.h"

using namespace std;

class FuncInfo {
private:
    string funcName;
    set<string> srcFile; //换成 set  path
    set<string> codeSet;
    map<int, struct OffsetInfo> map_offset_src; // map: offset -> srcfile name, line, code          存储指向srcFile的指针      偏移量 int
    //汇编code 全部放进一个vector  index索引
    // vector -> struct
public:
    FuncInfo();
    FuncInfo(string funcName);

    void addSrcFile(string filePath, string fileLine);
    set<string> getSrcFile();

    void addOffsetSrc(int offset, string filePath, string line, string code);
    map<int, struct OffsetInfo> getOffsetSrc();

    OffsetInfo searchOffset(int offset);

    void printSrcFile();
    void printOffset();
};


#endif //TEST_FUNCINFO_H

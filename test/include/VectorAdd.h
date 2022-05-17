//
// Created by Minghao Guo on 2022/5/14.
//

#ifndef TEST_VECTORADD_H
#define TEST_VECTORADD_H

#include <string>
#include <map>
#include <vector>

using namespace std;

class VectorAdd {
private:
    string funcName;
    vector<string> srcFile; //换成 set  path
    map<string, vector<string>> map_offset_src; // map: offset -> srcfile name, line, code          存储指向srcFile的指针      偏移量 int
    //汇编code 全部放进一个vector  index索引
    // vector -> struct
public:
    VectorAdd();
    VectorAdd(string funcName);

    void addSrcFile(string fileName, string fileLine);
    vector<string> getSrcFile();

    void addOffsetSrc(string offset, string fileName, string line, string code);
    map<string, vector<string>> getOffsetSrc();

    vector<string> searchOffset(string offset);

    void printSrcFile();
    void printOffset();
};


#endif //TEST_VECTORADD_H

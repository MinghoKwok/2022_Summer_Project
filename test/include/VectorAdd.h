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
    vector<string> srcFile;
    map<string, vector<string>> map_offset_src; // map: offset -> srcfile name, line, code
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

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
    vector<map<string, vector<string>>> vec; // map: offset -> srcfile name, line
public:
    VectorAdd();
    VectorAdd(string funcName);
};


#endif //TEST_VECTORADD_H

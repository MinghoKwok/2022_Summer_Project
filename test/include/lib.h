#ifndef TEST_LIB_H
#define TEST_LIB_H

#include <fstream>
#include "../include/FuncInfo.h"
#include "../include/helpFunc.h"

using namespace std;

extern map<string, FuncInfo> map_FuncInfos;

void init(string path);

map<string, FuncInfo> mapOffset(string dataPath);

//void analyzeLines(stringstream *ss);

#endif //TEST_LIB_H

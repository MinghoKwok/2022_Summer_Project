#ifndef TEST_HELPFUNC_H
#define TEST_HELPFUNC_H
#include <iostream>
#include "FuncInfo.h"

using namespace std;

int hexToInt(string str);

vector<string> splitCode(string code);
void analyzeCode(FuncInfo FI);
int regCount(string numStr);

#endif //TEST_HELPFUNC_H

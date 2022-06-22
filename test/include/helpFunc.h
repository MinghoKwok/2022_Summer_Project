#ifndef TEST_HELPFUNC_H
#define TEST_HELPFUNC_H
#include <iostream>
#include "FuncInfo.h"
#include <cstring>
#include <algorithm>
using namespace std;

int hexToInt(string str);

vector<string> splitCode(string code);
void searchOffset(FuncInfo FI, int search_offset);
int regCount(string numStr);
bool ifContainsWide(string code);
string splitFuncType(string code);

#endif //TEST_HELPFUNC_H

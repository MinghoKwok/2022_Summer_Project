#ifndef TEST_OFFSETINFO_H
#define TEST_OFFSETINFO_H

#include <string>

using namespace std;

struct OffsetInfo{
    set<string>::iterator src_path;
    int src_line;
    set<string>::iterator code;
};

#endif //TEST_OFFSETINFO_H

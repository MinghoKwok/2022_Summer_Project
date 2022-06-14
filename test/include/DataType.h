#ifndef TEST_DATATYPE_H
#define TEST_DATATYPE_H

#include <string>
#include <map>

using namespace std;

struct DataType {
    int type;       // 0 -> INT, 1 -> FP
    int version;    // 32, 64
};


#endif //TEST_DATATYPE_H

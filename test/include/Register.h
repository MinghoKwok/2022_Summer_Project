#ifndef TEST_REGISTER_H
#define TEST_REGISTER_H

#include <string>
#include <map>

using namespace std;

struct Register{
    string name;
    int count;
    int active_count;
    map<int, int> reg_act;  // vector
};

#endif //TEST_REGISTER_H

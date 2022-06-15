#include "regex.h"

#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

vector<string> getMatch(string reg, string inputStr)
{


    regex ip_reg(reg);
    smatch matchResult;
    vector<string> res;


    //string inputStr = "\t//## File \"/home/findhao/NVIDIA_CUDA-11.4_Samples/0_Simple/vectorAdd/vectorAdd.cu\", line 35";
    //std::getline(std::cin,inputStr);


    //正则匹配
    if (regex_match(inputStr,matchResult,ip_reg))
    {
        //cout << "Match: " << endl;
        for (size_t i = 1; i < matchResult.size(); ++i)
        {
            //cout << matchResult[i] << endl;
            res.push_back((string)matchResult[i]);
        }
    } else {
        //cout << "Not Match!";
    }

    return res;

}


void regex_test() {

    string filePath("789.123.456");
    regex pattern("(.*)\\.123\\.456");

    // filePath 是否匹配 pattern
    bool matched = std::regex_match(filePath, pattern);
    cout << boolalpha << matched;            // true
}

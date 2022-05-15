#include "regex.h"

#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

vector<string> getMatch(string reg, string inputStr)
{


    std::regex ip_reg(reg);
    std::smatch matchResult;
    vector<string> res;


    //string inputStr = "\t//## File \"/home/findhao/NVIDIA_CUDA-11.4_Samples/0_Simple/vectorAdd/vectorAdd.cu\", line 35";
    //std::getline(std::cin,inputStr);


    //正则匹配
    if (std::regex_match(inputStr,matchResult,ip_reg))
    {
        //cout << "Match: " << endl;
        for (size_t i = 1; i < matchResult.size(); ++i)
        {
            //cout << matchResult[i] << endl;
            res.push_back((string)matchResult[i]);
        }
    }
    else
    {
        //cout << "Not Match!";
    }

    return res;

}

vector<string> getSearch(string reg, string inputStr) {

}

void regex_test() {

    string filename("789.123.456");
    regex pattern("(.*)\\.123\\.456");

    // filename 是否匹配 pattern
    bool matched = std::regex_match(filename, pattern);
    cout << boolalpha << matched;            // true
}

#include "regex.h"

#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

void getSrcFile(string reg)
{


    std::regex ip_reg(reg);
    std::smatch matchResult;



    string inputStr = "\t//## File \"/home/findhao/NVIDIA_CUDA-11.4_Samples/0_Simple/vectorAdd/vectorAdd.cu\", line 35";
    //std::getline(std::cin,inputStr);


    //正则匹配
    if (std::regex_match(inputStr,matchResult,ip_reg))
    {
        cout << "Match: " << endl;
        //打印子表达式结果
        for (size_t i = 1; i < matchResult.size(); ++i)
        {
            cout << matchResult[i] << endl;
        }
    }
    else
    {
        cout << "Not Match!";
    }

}

void regex_test() {

    string filename("789.123.456");
    regex pattern("(.*)\\.123\\.456");

    // filename 是否匹配 pattern
    bool matched = std::regex_match(filename, pattern);
    cout << boolalpha << matched;            // true
}

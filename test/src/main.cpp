#include <iostream>
#include <fstream>
#include <regex>
#include "../include/regex_test.h"
#include "../include/FuncInfo.h"
#include "../include/helpFunc.h"

using namespace std;

void mapOffset(string dataPath);

int main() {

    mapOffset("../data/vectoradd.txt");

    return 0;
}

void mapOffset(string dataPath) {


    ifstream myfile (dataPath);
    ofstream outfile("../data/result2.txt");
    string tempStr;
    bool begin = false; //identified function name， assembly part begin

    if(!myfile){
        cout << "Unable to open myfile";
        exit(1); // terminate with error

    }
    if(!outfile){
        cout << "Unable to open otfile";
        exit(1); // terminate with error

    }




    // Analyze line by line
    FuncInfo *FI = nullptr;
    map<string, FuncInfo> map_FuncInfos; // function name -> FuncInfo Objects   //vector还是map
    vector<FuncInfo> vec_FuncInfos;

    string filePath = "no src file";
    string fileLine = "-1";
    while (getline(myfile, tempStr)) {
        // match function name
        vector<string> function_name = getMatch("//-+ \\.text\\.(.*) -+", tempStr);
        if (!function_name.empty()) {   // match 到 function 了
            if (FI != nullptr)
                vec_FuncInfos.push_back(*FI);

            FuncInfo tempObj(function_name[0]);
            FI = &tempObj;
            filePath = "no src file";
            fileLine = "-1";
            //FI->addSrcFile(filePath, fileLine);       //报139错

            //map_FuncInfos.insert(pair<string, FuncInfo>(tempObj.getFuncName(), tempObj));

            //cout << tempObj.getFuncName() << endl;

        }


        // match register name
//        FI->setRegister("GPR", 10);
//        FI->setRegister("PRED", 1);


        // match src file and corresponding line
        vector<string> src_file = getMatch("\t//## File \"(.*)\", line ([0-9]*)(.*)", tempStr);
        if (!src_file.empty()) {

            filePath = src_file[0];
            fileLine = src_file[1];
            //cout << "Source File    Name: " << filePath << "       Line: " << fileLine << endl;
            FI->addSrcFile(filePath, fileLine);
        }




        // match offset and assembly code
        vector<string> offset_code = getMatch("        /\\*(.*)\\*/( +)(.*); (.*)", tempStr);
        if (!offset_code.empty()) {
            FI->addSrcFile(filePath, fileLine);     //解决没有源文件情形，不知道为什么加在前面会报139错

            int offset = hexToInt(offset_code[0]);
            string code = offset_code[2];
            //outfile << "Offset: " << offset << "       Assembly Code: " << code << "\n";

            // construct register
            Register reg_GPR;
            reg_GPR.count = 10;
            reg_GPR.name = "GPR";
            vector<string> reg_status = getMatch("(.*)\\/\\/ \\|(.*)\\|(.*)\\|", tempStr);  // \/\/ \|(.*)\|(.*)\|
            if (!reg_status.empty()) {
 //               cout << reg_status[1][8] << endl;  // GPR
//                cout << reg_status[2] << endl;  // PRED
                string str_GPR = reg_status[1];
                string str_PRED = reg_status[2];
                reg_GPR.occupied_count = str_GPR[2] - '0';
                int start = 2;
                for (int i = 1; i <= reg_GPR.count; i++) {
                    int index = start + i * 2;
                    switch (str_GPR[index]) {
                        case ' ':
                            reg_GPR.reg_status.push_back(0);
                            break;
                        case '^':
                            reg_GPR.reg_status.push_back(1);
                            break;
                        case 'v':
                            reg_GPR.reg_status.push_back(2);
                            break;
                        case 'x':
                            reg_GPR.reg_status.push_back(3);
                            break;
                        case ':':
                            reg_GPR.reg_status.push_back(4);
                            break;
                        default:
                            cout << "unindentify:" << str_GPR[index] << endl;
                    }
                }
            } else {
                cout << "no" << endl;
            }

            //  add to the object
            FI->addOffsetSrc(offset, filePath, fileLine, code, reg_GPR);
        }
    }
    if (FI != nullptr)
        vec_FuncInfos.push_back(*FI);


    // Show result (map)
    /*
    for (auto iter : map_FuncInfos) {
        cout << "Function Name: " << iter.second.getFuncName() << endl;
        //iter.second.printOffset();
//        for (auto iter1 : iter.second.getOffsetSrc()) {
//            cout << "Offset: " << iter1.first << "  Code: " << *iter1.second.code << endl;
//        }
        cout << endl << endl;
    }
     */

    //cout << "vec_FuncInfos size: " << vec_FuncInfos.size() << endl;

    for (int i = 0; i < vec_FuncInfos.size(); i++) {
        //cout << vec_FuncInfos[i].getFuncName() << endl;
        //vec_FuncInfos[i].printSrcFile();          // Print source file and line
        //vec_FuncInfos[i].printOffset();           // Print mappings
        //vec_FuncInfos[i].searchOffset(0);       // Test search offset
    }





    myfile.close();
    outfile.close();
}

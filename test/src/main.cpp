#include <iostream>
#include <fstream>
#include <regex>
#include "../include/regex_test.h"
#include "../include/FuncInfo.h"
#include "../include/helpFunc.h"
#include "../include/Register.h"

using namespace std;

vector<FuncInfo> mapOffset(string dataPath);

int main() {

    // mapOffset
    vector<FuncInfo> vec_FuncInfos = mapOffset("../data/vectoradd.txt");
    /*
    SASSLineInfo OI = vec_FuncInfos[0].searchOffset(144);
    Register reg_GPR = OI.reg_GPR;
    string code = *OI.code;
    //cout << code << endl << endl;
    vector<string> vec_code = splitCode(code);
     */
    analyzeCode(vec_FuncInfos[0]);

    return 0;
}

vector<FuncInfo> mapOffset(string dataPath) {


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
    map<string, FuncInfo> map_FuncInfos; // function name -> FuncInfo Objects   //vector还是map  增加时，如果发现key已经存在，报错
    vector<FuncInfo> vec_FuncInfos;

    string filePath = "no src file";
    string fileLine = "-1";
    int reg_GPR_size = -1;
    int reg_PRED_size = -1;
    int reg_UGPR_size = -1;
    int reg_UPRED_size = -1;
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

            reg_GPR_size = -1;
            reg_PRED_size = -1;
            reg_UGPR_size = -1;
            reg_UPRED_size = -1;
            //FI->addSrcFile(filePath, fileLine);       //报139错

            //map_FuncInfos.insert(pair<string, FuncInfo>(tempObj.getFuncName(), tempObj));

            //cout << tempObj.getFuncName() << endl;

        }


        // match register name
//        FI->setRegister("GPR", 10);
//        FI->setRegister("PRED", 1);

        // count each register
        vector<string> reg_count = getMatch("(.*)\\/\\/ \\|\\s*#(.*)\\s+\\|\\s*#(.*)\\s+\\|", tempStr);
        if (!reg_count.empty()) {
            reg_GPR_size = reg_count[1].back() - '0' + 1;
            cout << "reg_GPR_size: " << reg_GPR_size << endl;
            reg_PRED_size = reg_count[2].back() - '0' + 1;
            cout << "reg_PRED_size: " << reg_PRED_size << endl;
        }

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
            reg_GPR.size = reg_GPR_size;
            reg_GPR.name = "GPR";
            Register reg_PRED;
            reg_PRED.size = reg_PRED_size;
            reg_PRED.name = "PRED";
            vector<string> reg_status = getMatch("(.*)\\/\\/ \\|\\s*(.*)\\|\\s*(.*)\\|", tempStr);  // (.*)\/\/ \|\s*(.*)\|\s*(.*)\|    \s* 取代空格
            if (!reg_status.empty()) {
 //               cout << reg_status[1][8] << endl;  // GPR
//                cout << reg_status[2] << endl;  // PRED
                string str_GPR = reg_status[1];
                string str_PRED = reg_status[2];

                if (str_GPR.empty()) {  // no reg_GPR used now
                    reg_GPR.occupied_count = 0;
                } else {
                    reg_GPR.occupied_count = str_GPR[0] - '0';
                    int start = 0;
                    for (int i = 1; i <= reg_GPR.size; i++) {
                        int index = start + i * 2;
                        //cout << str_GPR[index] << endl;
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
                                cout << "Error: Unidentify:" << str_GPR[index] << endl;
                        }
                    }
                }

                if (str_PRED.empty()) {  // no reg_PRED used now
                    reg_PRED.occupied_count = 0;
                } else {
                    reg_PRED.occupied_count = str_PRED[0] - '0';
                    int start = 0;
                    for (int i = 0; i < reg_PRED.size; i++) {
                        int index = start + 1 + to_string(i).size();
                        switch (str_PRED[index]) {
                            case ' ':
                                reg_PRED.reg_status.push_back(0);
                                break;
                            case '^':
                                reg_PRED.reg_status.push_back(1);
                                break;
                            case 'v':
                                reg_PRED.reg_status.push_back(2);
                                break;
                            case 'x':
                                reg_PRED.reg_status.push_back(3);
                                break;
                            case ':':
                                reg_PRED.reg_status.push_back(4);
                                break;
                            default:
                                cout << "Error: Unidentify:" << str_PRED[index] << endl;
                        }
                    }
                }

            } else {
                cout << "Error: Not found reg_status." << endl;
            }

            //  add to the object
//            for (int i = 0; i < reg_GPR.reg_status.size(); i++) {
//                cout << reg_GPR.reg_status[i] << " ";
//            }
//            cout << endl;
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



    return vec_FuncInfos;
}

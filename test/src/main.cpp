#include <iostream>
#include <fstream>
#include <regex>
#include "../include/regex_test.h"
#include "../include/FuncInfo.h"
#include "../include/helpFunc.h"
#include "../include/Register.h"
// include lib.h  lib.cpp（写init）
using namespace std;

map<string, FuncInfo> mapOffset(string dataPath);
                                                                                    // 下周一测试更多txt
int main() {

    // mapOffset
    map<string, FuncInfo> map_FuncInfos = mapOffset("../data/castro.head_10000.txt");      //写成全局变量    // 声明定义在lib  init外面     init("/castro.txt")  init后 searchOffset
    cout << endl << "Count of kernels: " << map_FuncInfos.size() << endl << endl;

    //searchOffset(map_FuncInfos["_ZN3cub11EmptyKernelIvEEvv"], 0);
    searchOffset(map_FuncInfos["_ZN5amrex13launch_globalILi256EZNS_11ParallelForIiZNS_7BaseFabIiE6setValILNS_5RunOnE1EEEvRKiRKNS_3BoxENS_8DestCompENS_8NumCompsEEUliiiiE_vEENSt9enable_ifIXsr5amrex19MaybeDeviceRunnableIT0_vEE5valueEvE4typeERKNS_3Gpu10KernelInfoESA_T_OSF_EUlvE_EEvSF_"], 64);
    searchOffset(map_FuncInfos["_ZN5amrex13launch_globalILi256EZNS_11ParallelForIiZNS_7BaseFabIiE6setValILNS_5RunOnE1EEEvRKiRKNS_3BoxENS_8DestCompENS_8NumCompsEEUliiiiE_vEENSt9enable_ifIXsr5amrex19MaybeDeviceRunnableIT0_vEE5valueEvE4typeERKNS_3Gpu10KernelInfoESA_T_OSF_EUlvE_EEvSF_"], 144);
    searchOffset(map_FuncInfos["_ZN5amrex13launch_globalILi256EZNS_11ParallelForIiZNS_7BaseFabIiE6setValILNS_5RunOnE1EEEvRKiRKNS_3BoxENS_8DestCompENS_8NumCompsEEUliiiiE_vEENSt9enable_ifIXsr5amrex19MaybeDeviceRunnableIT0_vEE5valueEvE4typeERKNS_3Gpu10KernelInfoESA_T_OSF_EUlvE_EEvSF_"], 240);
    return 0;
}

map<string, FuncInfo> mapOffset(string dataPath) {


    ifstream myfile (dataPath);
//    ofstream outfile("../data/result2.txt");
    string tempStr;

    if(!myfile){
        cout << "Unable to open myfile";
        exit(1); // terminate with error

    }
//    if(!outfile){
//        cout << "Unable to open otfile";
//        exit(1); // terminate with error
//    }




    // Analyze line by line
    FuncInfo *FI = nullptr;
    map<string, FuncInfo> map_FuncInfos; // function name -> FuncInfo Objects   //vector还是map  增加时，如果发现key已经存在，报错
    //vector<FuncInfo> vec_FuncInfos;

    string filePath = "no src file";
    string fileLine = "-1";
    int reg_GPR_size = -1;
    int reg_PRED_size = -1;
    int reg_UGPR_size = -1;
    int reg_UPRED_size = -1;
    while (getline(myfile, tempStr)) {
        if (tempStr.empty())
            continue;

        if (tempStr[8] == '/') {    // if (tempStr.find("/*") != tempStr.npos)
            // match offset and assembly code
            vector<string> offset_code = getMatch("\\s*/\\*(.*)\\*/( +)(.*); (.*)\\/\\/ \\|\\s*(.*)\\|\\s*(.*)\\|\\s*(.*)\\|\\s*(.*)\\|", tempStr);
            if (!offset_code.empty()) {
                FI->addSrcFile(filePath, fileLine);     //解决没有源文件情形，不知道为什么加在前面会报139错

                int offset = hexToInt(offset_code[0]);
                string code = offset_code[2];
                //outfile << "Offset: " << offset << "       Assembly Code: " << code << "\n";

                // construct register
                auto *reg_GPR = new Register();
                reg_GPR->size = reg_GPR_size;
                reg_GPR->name = "GPR";
                auto *reg_PRED = new Register();
                reg_PRED->size = reg_PRED_size;
                reg_PRED->name = "PRED";
                auto *reg_UGPR = new Register();
                reg_UGPR->size = reg_UGPR_size;
                reg_UGPR->name = "UGPR";
                auto *reg_UPRED = new Register();
                reg_UPRED->size = reg_UPRED_size;
                reg_UPRED->name = "UPRED";
                //vector<string> reg_status = getMatch("(.*)\\/\\/ \\|\\s*(.*)\\|\\s*(.*)\\|\\s*(.*)\\|\\s*(.*)\\|", tempStr);  // (.*)\/\/ \|\s*(.*)\|\s*(.*)\|    \s* 取代空格
                string str_GPR = offset_code[4];
                string str_PRED = offset_code[5];
                string str_UGPR = offset_code[6];
                string str_UPRED = offset_code[7];

                if (str_GPR.empty()) {  // no reg_GPR used now
                    reg_GPR->occupied_count = 0;
                    vector<int> reg_s(reg_GPR->size, 0);
                    reg_GPR->reg_status = reg_s;
                } else {
                    int index = str_GPR.find(' ') - 1;  // active number 的末位
                    reg_GPR->occupied_count = atoi(str_GPR.substr(0,index + 1).c_str());
                    //cout << "GPR occupied_count: " << reg_GPR->occupied_count << endl;
                    for (int i = 0; i < reg_GPR->size; i++) {
                        index = index + 1 + to_string(i).size();
                        //cout << str_GPR[index] << endl;
                        switch (str_GPR[index]) {
                            case ' ':
                                reg_GPR->reg_status.push_back(0);
                                break;
                            case '^':
                                reg_GPR->reg_status.push_back(1);
                                break;
                            case 'v':
                                reg_GPR->reg_status.push_back(2);
                                break;
                            case 'x':
                                reg_GPR->reg_status.push_back(3);
                                break;
                            case ':':
                                reg_GPR->reg_status.push_back(4);
                                break;
                            default:
                                cout << "Error: Unidentify:" << str_GPR[index] << endl;
                        }
                    }
                }

                if (str_PRED.empty()) {  // no reg_PRED used now
                    reg_PRED->occupied_count = 0;
                    vector<int> reg_s(reg_PRED->size, 0);
                    reg_PRED->reg_status = reg_s;
                } else {
                    int index = str_PRED.find(' ') - 1;  // active number 的末位
                    reg_PRED->occupied_count = atoi(str_PRED.substr(0,index + 1).c_str());
                    for (int i = 0; i < reg_PRED->size; i++) {
                        index = index + 1 + to_string(i).size();
                        switch (str_PRED[index]) {
                            case ' ':
                                reg_PRED->reg_status.push_back(0);
                                break;
                            case '^':
                                reg_PRED->reg_status.push_back(1);
                                break;
                            case 'v':
                                reg_PRED->reg_status.push_back(2);
                                break;
                            case 'x':
                                reg_PRED->reg_status.push_back(3);
                                break;
                            case ':':
                                reg_PRED->reg_status.push_back(4);
                                break;
                            default:
                                cout << "Error: Unidentify:" << str_PRED[index] << endl;
                        }
                    }
                }

                if (str_UGPR.empty()) {  // no reg_UGPR used now
                    reg_UGPR->occupied_count = 0;
                    vector<int> reg_s(reg_UGPR->size, 0);
                    reg_UGPR->reg_status = reg_s;
                } else {
                    int index = str_UGPR.find(' ') - 1;  // active number 的末位
                    reg_UGPR->occupied_count = atoi(str_UGPR.substr(0,index + 1).c_str());
                    for (int i = 0; i < reg_UGPR->size; i++) {
                        index = index + 1 + to_string(i).size();
                        switch (str_UGPR[index]) {
                            case ' ':
                                reg_UGPR->reg_status.push_back(0);
                                break;
                            case '^':
                                reg_UGPR->reg_status.push_back(1);
                                break;
                            case 'v':
                                reg_UGPR->reg_status.push_back(2);
                                break;
                            case 'x':
                                reg_UGPR->reg_status.push_back(3);
                                break;
                            case ':':
                                reg_UGPR->reg_status.push_back(4);
                                break;
                            default:
                                cout << "Error: Unidentify:" << str_UGPR[index] << endl;
                        }
                    }
                }

                if (str_UPRED.empty()) {  // no reg_UPRED used now
                    reg_UPRED->occupied_count = 0;
                    vector<int> reg_s(reg_UPRED->size, 0);
                    reg_UPRED->reg_status = reg_s;
                } else {
                    int index = str_UPRED.find(' ') - 1;  // active number 的末位
                    reg_UPRED->occupied_count = atoi(str_UPRED.substr(0,index + 1).c_str());
                    for (int i = 0; i < reg_UPRED->size; i++) {
                        index = index + 1 + to_string(i).size();
                        switch (str_UPRED[index]) {
                            case ' ':
                                reg_UPRED->reg_status.push_back(0);
                                break;
                            case '^':
                                reg_UPRED->reg_status.push_back(1);
                                break;
                            case 'v':
                                reg_UPRED->reg_status.push_back(2);
                                break;
                            case 'x':
                                reg_UPRED->reg_status.push_back(3);
                                break;
                            case ':':
                                reg_UPRED->reg_status.push_back(4);
                                break;
                            default:
                                cout << "Error: Unidentify:" << str_UPRED[index] << endl;
                        }
                    }
                }

                //  add to the object
                FI->addOffsetSrc(offset, filePath, fileLine, code, reg_GPR, reg_PRED, reg_UGPR, reg_UPRED);

                continue;
            }

        } else {
            // match src file and corresponding line
            vector<string> src_file = getMatch("((\\s|\\t)*)\\/\\/## File \"(.*)\", line ([0-9]*)(.*)", tempStr);     //补上 else 排除
            if (!src_file.empty()) {
                filePath = src_file[2];
                fileLine = src_file[3];
                cout << "   Source File    Name: " << filePath << "       Line: " << fileLine << endl;
                FI->addSrcFile(filePath, fileLine);

                continue;
            }


            // match function name
            vector<string> function_name = getMatch("//-+ \\.text\\.(.*) -+", tempStr);
            if (!function_name.empty()) {   // match 到 function 了
                if (FI != nullptr) {
                    //vec_FuncInfos.push_back(*FI);
                    map_FuncInfos.insert(pair<string, FuncInfo>(FI->getFuncName(), *FI));
                    //cout << "test: " << map_FuncInfos[FI->getFuncName()].getFuncName() << endl;
                }

                string str(function_name[0]);
                FuncInfo *tempObj = new FuncInfo(str);  // 改存 stack 为 heap
                FI = tempObj;
                filePath = "no src file";
                fileLine = "-1";

                reg_GPR_size = -1;
                reg_PRED_size = -1;
                reg_UGPR_size = -1;
                reg_UPRED_size = -1;
                //FI->addSrcFile(filePath, fileLine);       //报139错

                cout << "Create: " << FI->getFuncName() << endl;
                continue;
            }


            // count each register          // 写进function的else
            vector<string> reg_count = getMatch("(.*)\\/\\/ \\|\\s*#(.*)\\s+\\|\\s*#(.*)\\s+\\|\\s*#(.*)\\s+\\|\\s*#(.*)\\s+\\|", tempStr);
            if (!reg_count.empty()) {
                reg_GPR_size = regCount(reg_count[1]);
                //cout << "reg_GPR_size: " << reg_GPR_size << endl;
                reg_PRED_size = regCount(reg_count[2]);
                //cout << "reg_PRED_size: " << reg_PRED_size << endl;
                reg_UGPR_size = regCount(reg_count[3]);
                //cout << "reg_UGPR_size: " << reg_UGPR_size << endl;
                reg_UPRED_size = regCount(reg_count[4]);
                //cout << "reg_UPRED_size: " << reg_UPRED_size << endl;

                continue;
            }
        }

    }


    if (FI != nullptr) {
        //vec_FuncInfos.push_back(*FI);
        map_FuncInfos.insert(pair<string, FuncInfo>(FI->getFuncName(), *FI));
    }


    // Show result (map)
    /*
    cout << endl << "map_FuncInfos size: " << map_FuncInfos.size() << endl;
    for (auto iter : map_FuncInfos) {
        string funcName = iter.second.getFuncName();
        cout << "Function Name: " << funcName << endl;
        //iter.second.printOffset();
//        for (auto iter1 : iter.second.getOffsetSrc()) {
//            cout << "Offset: " << iter1.first << "  Code: " << *iter1.second.code << endl;
//        }
        map_FuncInfos[funcName].searchOffset(0);
        cout << endl;
    }
     */


//    cout << "vec_FuncInfos size: " << vec_FuncInfos.size() << endl;
//
//    for (int i = 0; i < vec_FuncInfos.size(); i++) {
//        cout << vec_FuncInfos[i].getFuncName() << endl;
//        //vec_FuncInfos[i].printSrcFile();          // Print source file and line
//        //vec_FuncInfos[i].printOffset();           // Print mappings
//        vec_FuncInfos[i].searchOffset(32);       // Test search offset
//    }





    myfile.close();


    return map_FuncInfos;
}

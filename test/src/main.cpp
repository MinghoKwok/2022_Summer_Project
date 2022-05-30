#include <iostream>
#include <fstream>
#include <regex>
#include "../include/regex_test.h"
#include "../include/FuncInfo.h"
#include "../include/helpFunc.h"

using namespace std;

void mapOffset(string dataPath);

int main() {

    mapOffset("../data/castro.head_10000.txt");

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
            //FI->addSrcFile(filePath, fileLine);

            //map_FuncInfos.insert(pair<string, FuncInfo>(tempObj.getFuncName(), tempObj));

            //cout << tempObj.getFuncName() << endl;
            //tempObj.printOffset();
            //tempObj.printSrcFile();
            //FI.clear();


            //cout << "This is function name： " << function_name[0] << endl;
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
            FI->addOffsetSrc(offset, filePath, fileLine, code);
        }
    }
    if (FI != nullptr)
        vec_FuncInfos.push_back(*FI);


    // Show result
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


    //cout << map_FuncInfos.size() << endl;
    cout << vec_FuncInfos.size() << endl;
//    for (int i = 0; i < vec_FuncInfos.size(); i++) {
//        cout << vec_FuncInfos[i].getFuncName() << endl;
//        vec_FuncInfos[i].printSrcFile();
//        vec_FuncInfos[i].printOffset();
//    }

    for (int i = 0; i < vec_FuncInfos.size(); i++) {
        vec_FuncInfos[i].printSrcFile();
        vec_FuncInfos[i].printOffset();
        //vec_FuncInfos[i].searchOffset(0);
    }




    // Print source file and line
    //FI.printSrcFile();

    //cout << endl << endl;

    // Print mappings
    //FI.printOffset();

    //cout << endl << endl;

    // Test search offset
    //OffsetInfo offset_res = FI.searchOffset(48);








    // string.find()   method
    /*
    while (getline(myfile, tempStr)) {
        if (!begin) {
            auto pos_functionName = tempStr.find(functionName);
            if (pos_functionName == 0) {
                begin = true;
                cout << "Assembly part begin:" << endl;
            }
        } else {
            auto pos_newLine = tempStr.find("//##");
            if (pos_newLine != tempStr.npos) { // //##  analyze a new line
                outfile << tempStr << "\n";

                //analyze source file path and name
                auto pos_filePath_1 = tempStr.find("File");
                auto pos_filePath_2 = tempStr.find(", line");
                string src_file = tempStr.substr(pos_filePath_1 + 6, pos_filePath_2 - pos_filePath_1 - 7);
                outfile << "Source File: " << src_file << "\n";

                //analyze the num of line
                auto pos_lineNum_1 = tempStr.find(", line");
                auto pos_lineNum_2 = tempStr.find("// +");
                string line_num = tempStr.substr(pos_lineNum_1 + 7, pos_lineNum_2 - pos_lineNum_1 - 7);
                outfile << "Line Num: " << line_num << "\n\n";
            }
        }




    }
    */

    myfile.close();
    outfile.close();
}

//void mapOffset(string dataPath) {
//
//
//    ifstream myfile (dataPath);
//    ofstream outfile("../data/result2.txt");
//    string tempStr;
//    bool begin = false; //identified function name， assembly part begin
//
//    if(!myfile){
//        cout << "Unable to open myfile";
//        exit(1); // terminate with error
//
//    }
//    if(!outfile){
//        cout << "Unable to open otfile";
//        exit(1); // terminate with error
//
//    }
//
//
//
//
//    // Analyze line by line
//    int count = -1;
//
//    map<string, FuncInfo> map_FuncInfos; // function name -> FuncInfo Objects   //vector还是map
//    vector<FuncInfo> vec_FuncInfos;
//
//    string filePath;
//    string fileLine;
//    while (getline(myfile, tempStr)) {
//        // match function name
//        vector<string> function_name = getMatch("//-+ \\.text\\.(.*) -+", tempStr);
//        if (function_name.size() != 0) {
//            count++;
//            FuncInfo FI = FuncInfo(function_name[0]);
//            vec_FuncInfos.push_back(FI);
//
//            //cout << "This is function name： " << function_name[0] << endl;
//        }
//
//
//
//        // match src file and corresponding line
//        vector<string> src_file = getMatch("\t//## File \"(.*)\", line ([0-9]*)(.*)", tempStr);
//        if (src_file.size() != 0) {
//
//            filePath = src_file[0];
//            fileLine = src_file[1];
//            //cout << "Source File    Name: " << filePath << "       Line: " << fileLine << endl;
//            vec_FuncInfos[count].addSrcFile(filePath, fileLine);
//        }
//
//        // match offset and assembly code
//        vector<string> offset_code = getMatch("        /\\*(.*)\\*/( +)(.*); (.*)", tempStr);
//        if (offset_code.size() != 0) {
//
//            int offset = hexToInt(offset_code[0]);
//            string code = offset_code[2];
//            //outfile << "Offset: " << offset << "       Assembly Code: " << code << "\n";
//            vec_FuncInfos[count].addOffsetSrc(offset, filePath, fileLine, code);
//        }
//    }
//
//    // Show result
//    /*
//    for (auto iter : map_FuncInfos) {
//        cout << "Function Name: " << iter.second.getFuncName() << endl;
//        //iter.second.printOffset();
////        for (auto iter1 : iter.second.getOffsetSrc()) {
////            cout << "Offset: " << iter1.first << "  Code: " << *iter1.second.code << endl;
////        }
//        cout << endl << endl;
//    }
//     */
//
//
//    //cout << map_FuncInfos.size() << endl;
//    cout << vec_FuncInfos.size() << endl;
////    for (int i = 0; i < vec_FuncInfos.size(); i++) {
////        cout << vec_FuncInfos[i].getFuncName() << endl;
////        vec_FuncInfos[i].printSrcFile();
////        vec_FuncInfos[i].printOffset();
////    }
//
//    vec_FuncInfos[0].printSrcFile();
//    vec_FuncInfos[0].printOffset();
//    //vec_FuncInfos[0].searchOffset(176);
//
//
//
//    // Print source file and line
//    //FI.printSrcFile();
//
//    //cout << endl << endl;
//
//    // Print mappings
//    //FI.printOffset();
//
//    //cout << endl << endl;
//
//    // Test search offset
//    //OffsetInfo offset_res = FI.searchOffset(48);
//
//
//
//
//
//
//
//
//    // string.find()   method
//    /*
//    while (getline(myfile, tempStr)) {
//        if (!begin) {
//            auto pos_functionName = tempStr.find(functionName);
//            if (pos_functionName == 0) {
//                begin = true;
//                cout << "Assembly part begin:" << endl;
//            }
//        } else {
//            auto pos_newLine = tempStr.find("//##");
//            if (pos_newLine != tempStr.npos) { // //##  analyze a new line
//                outfile << tempStr << "\n";
//
//                //analyze source file path and name
//                auto pos_filePath_1 = tempStr.find("File");
//                auto pos_filePath_2 = tempStr.find(", line");
//                string src_file = tempStr.substr(pos_filePath_1 + 6, pos_filePath_2 - pos_filePath_1 - 7);
//                outfile << "Source File: " << src_file << "\n";
//
//                //analyze the num of line
//                auto pos_lineNum_1 = tempStr.find(", line");
//                auto pos_lineNum_2 = tempStr.find("// +");
//                string line_num = tempStr.substr(pos_lineNum_1 + 7, pos_lineNum_2 - pos_lineNum_1 - 7);
//                outfile << "Line Num: " << line_num << "\n\n";
//            }
//        }
//
//
//
//
//    }
//    */
//
//    myfile.close();
//    outfile.close();
//}
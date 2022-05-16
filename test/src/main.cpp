#include <iostream>
#include <fstream>
#include <regex>
#include "../include/regex_test.h"
#include "../include/VectorAdd.h"

using namespace std;

void mapOffset(string functionName);

int main() {

    mapOffset("_Z9vectorAddPKfS0_Pfi");

    return 0;
}

void mapOffset(string functionName) {
    VectorAdd VA = VectorAdd(functionName);

    ifstream myfile ("../data/vectoradd.txt");
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
    string fileName;
    string fileLine;
    while (getline(myfile, tempStr)) {
        // match src file and corresponding line
        vector<string> srcFile = getMatch("\t//## File \"(.*)\", line ([0-9]*)(.*)", tempStr);
        if (srcFile.size() != 0) {
//            for (int i = 0; i < srcFile.size(); i++)
//                cout << srcFile[i] << endl;

            fileName = srcFile[0];
            fileLine = srcFile[1];
            //cout << "Source File    Name: " << fileName << "       Line: " << fileLine << endl;
            VA.addSrcFile(fileName, fileLine);
        }

        // match offset and assembly code
        vector<string> offset_code = getMatch("        /\\*(.*)\\*/( +)(.*); (.*)", tempStr);
        if (offset_code.size() != 0) {
//            for (int i = 0; i < offset_code.size(); i++)
//                cout << offset_code[i] << endl;

            string offset = offset_code[0];
            string code = offset_code[2];
            //cout << "Offset: " << offset << "       Assembly Code: " << code << endl;
            VA.addOffsetSrc(offset, fileName, fileLine, code);
        }
    }


    // Print source file and line
    vector<string> srcFile = VA.getSrcFile();
    for (int i = 0; i < srcFile.size(); i++)
        cout << srcFile[i] << endl;
    // Print mappings
    vector<map<string, vector<string>>> offset_src = VA.getOffsetSrc();
    for (int i = 0; i < offset_src.size(); i++) {
        auto iter = offset_src[i].begin();
        while (iter != offset_src[i].end()) {
            cout << "Offset: " << iter->first << endl;

            cout << "   Src File: " << iter->second[0] << "     Line: " << iter->second[1] << endl;
            cout << "   Code: " << iter->second[2] << endl;

            iter++;
        }
    }


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
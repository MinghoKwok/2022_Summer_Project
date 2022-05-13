#include <iostream>
#include <fstream>

using namespace std;

void mapOffset(string functionName);

int main() {

    //mapOffset("_Z9vectorAddPKfS0_Pfi");

    return 0;
}

void mapOffset(string functionName) {
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


    myfile.close();
    outfile.close();
}
#include "../include/helpFunc.h"
#include <sstream>
#include <vector>

using namespace std;

int hexToInt(string str) {
    int len = str.size();
    int res = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'f')
            res = (10 + str[i] - 'a') + res * 16;
        else
            res = (str[i] - '0') + res * 16;
    }

    return res;
}

vector<string> splitCode(string code) { // 后续考虑并入类中
    string str;
    vector<string> vec_code;

    for (int i = 0; i < strlen(code.c_str()); i++) {
        if (str.empty()) {
            if (code[i] == ',' || code[i] == ' ' || code[i] == ';')
                continue;
            else {
                str.append(1, code[i]);
            }
        } else {
            if (code[i] == ',' || code[i] == ' ' || code[i] == ';') {
                vec_code.push_back(str);
                str = "";
            } else {
                str.append(1, code[i]);
                if (i == strlen(code.c_str()) - 1)
                    vec_code.push_back(str);
            }
        }
    }

    for (int i = 0; i < vec_code.size(); i++) {
        cout << vec_code[i] << endl;
    }

    return vec_code;
}

void analyzeCode(FuncInfo FI) {
    int search_index = 144;
    OffsetInfo OI = FI.searchOffset(search_index);
    Register reg_GPR = OI.reg_GPR;
    string code = *OI.code;
    //cout << code << endl << endl;
    vector<string> vec_code = splitCode(code);

    if (vec_code[0] == "LDG.E.SYS") {   // Load
        cout << endl << "Load：" << endl;

        // find which reg is used (writen)
        int reg_write = -1;
        for (int i = 0; i < reg_GPR.reg_status.size(); i++) {
            if (reg_GPR.reg_status[i] == 1 || reg_GPR.reg_status[i] == 3) { // 1 -> 写 ^, 3 -> 读+写 x
                reg_write = i;
                break;
            }
        }

        // find where this reg is used
        for (search_index += 16; search_index <= (FI.getOffsetSrc().size() - 1) * 16; search_index += 16) {
            OI = FI.searchOffset(search_index);
            reg_GPR = OI.reg_GPR;
            if (reg_GPR.reg_status[reg_write] == 2 || reg_GPR.reg_status[reg_write] == 3) { // 2 -> 读 v, 3 -> 读+写 x
                break;  // find the read line
            }
        }

        code = *OI.code;
        vec_code = splitCode(code);

        if (vec_code[0] == "FADD") {
            cout << "Type is float" << endl;
        }
    }


}
#include "../include/helpFunc.h"
#include <sstream>
#include <vector>

using namespace std;

const vector<string> AssembFunc = {
//        the followings are integer instructions.
                                    "IMAD",
                                   "IMADSP",
                                   "IMUL",
                                   "IADD",
                                   "ISCADD",
                                   "ISAD",
                                   "IMNMX",
                                   "BFE",
                                   "BFI",
                                   "SHR",
                                   "SHL",
                                   "SHF",
                                   "LOP",
                                   "FLO",
                                   "ISET",
                                   "ISETP",
                                   "ICMP",
                                   "POPC",
//    the following are FP32 instructions
                                   "FFMA",
                                   "FADD",
                                   "FCMP",
                                   "FMUL",
                                   "FMNMX",
                                   "FSWZ",
                                   "FSET",
                                   "FSETP",
                                   "FCHK",
                                   "RRO",
//                                   the following are FP64 instructions
                                   "MUFU",
                                   "DFMA",
                                   "DADD",
                                   "DMUL",
                                   "DMNMX",
                                   "DSET",
                                   "DSETP"
};

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

vector<string> splitCode(string code) { // 后续考虑并入类中             // 找找 C++ regex 中 split
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
                if (str.find("@") == str.npos)
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

// 参数 offset, kernel name
void analyzeCode(FuncInfo FI, int search_offset) {
    SASSLineInfo SI = FI.searchOffset(search_offset);
    Register *reg_GPR = SI.reg_GPR;
    string code = *SI.code;
    //cout << code << endl << endl;
    vector<string> vec_code = splitCode(code);

    if (vec_code[0].find("LD") != vec_code[0].npos) {   // Load         // 改成 "LDG" 在不在 string 里    // 已知 offset       // store  "ST"
        cout << endl << "Load：" << endl;

        // find which reg is used (writen)
        int reg_write = -1;
        for (int i = 0; i < reg_GPR->reg_status.size(); i++) {
            if ((reg_GPR->reg_status[i] & 0x1) == 0x1) { // 1 -> 写 ^, 3 -> 读+写 x     // reg_GPR.reg_status[i] & 0x1  // 增加 map<1, reg4> 两者都用
                reg_write = i;
                break;
            }
        }

        // if reg_write == -1  error
        if (reg_write == -1) {
            cout << "ERROR: Not found any register is writen after loading the data." << endl;
        }

        // find where this reg is used (read)
        bool found = false;
        for (search_offset += 0x10; search_offset <= (FI.getOffsetSrc().size() - 1) * 0x10; search_offset += 0x10) { // 16 -> 0x10
            SI = FI.searchOffset(search_offset);
            reg_GPR = SI.reg_GPR;
            if ((reg_GPR->reg_status[reg_write] & 0x2) == 0x2) { // 2 -> 读 v, 3 -> 读+写 x     // & 0x2
                found = true;
                break;  // find the read line
            }
        }

        // if 没找到  error
        if (!found) {
            cout << "ERROR: Not found where the register just written is read after loading process." << endl;
        }

        code = *SI.code;
        vec_code = splitCode(code);

//        if (vec_code[0] == "FADD") {
//            cout << "Type is float" << endl;
//        }


        // enum / map
        auto iter = std::find(AssembFunc.begin(), AssembFunc.end(), vec_code[0]);
        if (iter != AssembFunc.end()) {
            int index = distance(AssembFunc.begin(), iter);     // iter - begin
            cout << "index: " << index << endl;
            if (index >= 18) {
                cout << "Type is float" << endl;        // 类型建structure  1. char type  0-> int  1-> float  2. 几bit的类型 32-> FP32  16-> FP64      返回这个结构体
            } else {
                cout << "Type is int" << endl;
            }
        } else {
            // error
            cout << "ERROR: Not found this function in the set." << endl;
        }


    }


}

// 计算reg个数的辅助函数
int regCount(string numStr) {
    stringstream input(numStr);
    string num;
    while (input>>num)
        continue;

    return atoi(num.c_str()) + 1;
}

bool ifContainsWide(string code) {
    stringstream sscode(code);
    string token;
    while (getline(sscode, token, '.')) {
        if (token == "WIDE")
            return true;
    }
    return false;
}

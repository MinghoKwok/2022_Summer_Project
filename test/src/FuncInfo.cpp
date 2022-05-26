#include "../include/FuncInfo.h"
#include <iostream>

FuncInfo::FuncInfo() {
    this->funcName = "_Z9vectorAddPKfS0_Pfi";
}

FuncInfo::FuncInfo(string funcName) {
    this->funcName = funcName;
}


void FuncInfo::addSrcFile(string filePath, string fileLine) {
    //this->srcFileSet.insert(filePath.append("     Line: ").append(fileLine));
    this->srcFileSet.insert(filePath);
}

set<string> FuncInfo::getSrcFile() {
    return this->srcFileSet;
}


void FuncInfo::addOffsetSrc(int offset, string filePath, string line, string code) {

    this->codeSet.insert(code); // 找找直接返回指针的set 函数

    OffsetInfo offset_info;
    offset_info.src_path = this->srcFileSet.find(filePath);
    offset_info.src_line = atoi(line.c_str());
    offset_info.code = this->codeSet.find(code);

    this->map_offset_src.insert(pair<int, struct OffsetInfo>(offset, offset_info));
}

map<int, struct OffsetInfo> FuncInfo::getOffsetSrc() {
    return this->map_offset_src;
}


OffsetInfo FuncInfo::searchOffset(int offset) {
    auto iter = this->map_offset_src.find(offset);
    if (iter == map_offset_src.end()) {
        OffsetInfo emptyOI;
        return emptyOI;
    } else {
        cout << "Offset: " << offset << endl;
        cout << "Src File Path: " << *iter->second.src_path << "   Line " << iter->second.src_line << endl << "Code: " << *iter->second.code << endl;
        return iter->second;
    }

}

void FuncInfo::printSrcFile() {
    for (auto i = this->srcFileSet.begin(); i != this->srcFileSet.end(); i++)
        cout << *i << endl;
}

void FuncInfo::printOffset() {
    map<int, struct OffsetInfo> offset_src = this->getOffsetSrc();
    auto iter = offset_src.begin();
    while (iter != offset_src.end()) {
        cout << "Offset: " << iter->first << endl;
        cout << "   Src File: " << *iter->second.src_path << "     Line: " << iter->second.src_line << endl;
        cout << "   Code: " << *iter->second.code << endl;

        iter++;
    }
}

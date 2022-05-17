#include "../include/VectorAdd.h"
#include <iostream>

VectorAdd::VectorAdd() {
    this->funcName = "_Z9vectorAddPKfS0_Pfi";
}

VectorAdd::VectorAdd(string funcName) {
    this->funcName = funcName;
    set<string> vec;
    this->srcFile = vec;
}


void VectorAdd::addSrcFile(string filePath, string fileLine) {
    //this->srcFile.insert(filePath.append("     Line: ").append(fileLine));
    this->srcFile.insert(filePath);
}

set<string> VectorAdd::getSrcFile() {
    return this->srcFile;
}


void VectorAdd::addOffsetSrc(int offset, string filePath, string line, string code) {

    OffsetInfo offset_info;
    offset_info.src_path = this->srcFile.find(filePath);
    offset_info.src_line = line;
    offset_info.code = code;

    this->map_offset_src.insert(pair<int, struct OffsetInfo>(offset, offset_info));
}

map<int, struct OffsetInfo> VectorAdd::getOffsetSrc() {
    return this->map_offset_src;
}


OffsetInfo VectorAdd::searchOffset(int offset) {
    auto iter = this->map_offset_src.find(offset);
    if (iter == map_offset_src.end()) {
        OffsetInfo emptyOI;
        return emptyOI;
    } else {
        cout << "Offset: " << offset << endl;
        cout << "Src File Path: " << *iter->second.src_path << "   Line " << iter->second.src_line << endl << "Code: " << iter->second.code << endl;
        return iter->second;
    }

}

void VectorAdd::printSrcFile() {
    for (auto i = this->srcFile.begin(); i != this->srcFile.end(); i++)
        cout << *i << endl;
}

//void VectorAdd::printOffset() {
//    map<string, vector<string>> offset_src = this->getOffsetSrc();
//    auto iter = offset_src.begin();
//    while (iter != offset_src.end()) {
//        cout << "Offset: " << iter->first << endl;
//        cout << "   Src File: " << iter->second[0] << "     Line: " << iter->second[1] << endl;
//        cout << "   Code: " << iter->second[2] << endl;
//
//        iter++;
//    }
//}

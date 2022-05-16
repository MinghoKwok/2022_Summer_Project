#include "../include/VectorAdd.h"
#include <iostream>

VectorAdd::VectorAdd() {
    this->funcName = "_Z9vectorAddPKfS0_Pfi";
}

VectorAdd::VectorAdd(string funcName) {
    this->funcName = funcName;
    vector<string> vec;
    this->srcFile = vec;
}


void VectorAdd::addSrcFile(string fileName, string fileLine) {
    this->srcFile.push_back(fileName.append("     Line: ").append(fileLine));
}

vector<string> VectorAdd::getSrcFile() {
    return this->srcFile;
}


void VectorAdd::addOffsetSrc(string offset, string fileName, string line, string code) {
    vector<string> vec;
    vec.push_back(fileName);
    vec.push_back(line);
    vec.push_back(code);

    map<string, vector<string>> tempMap;

    this->map_offset_src.insert(pair<string, vector<string>>(offset, vec));
}

map<string, vector<string>> VectorAdd::getOffsetSrc() {
    return this->map_offset_src;
}


vector<string> VectorAdd::searchOffset(string offset) {
    auto iter = this->map_offset_src.find(offset);
    if (iter == map_offset_src.end()) {
        vector<string> vec;
        return vec;
    } else {
        cout << "Offset: " << offset << endl;
        cout << "Src File Name: " << iter->second[0] << "   Line " << iter->second[1] << endl << "Code: " << iter->second[2] << endl;
        return iter->second;
    }

}

void VectorAdd::printSrcFile() {
    for (int i = 0; i < this->srcFile.size(); i++)
        cout << this->srcFile[i] << endl;
}

void VectorAdd::printOffset() {
    map<string, vector<string>> offset_src = this->getOffsetSrc();
    auto iter = offset_src.begin();
    while (iter != offset_src.end()) {
        cout << "Offset: " << iter->first << endl;
        cout << "   Src File: " << iter->second[0] << "     Line: " << iter->second[1] << endl;
        cout << "   Code: " << iter->second[2] << endl;

        iter++;
    }
}

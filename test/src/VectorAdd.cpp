#include "../include/VectorAdd.h"

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
    tempMap.insert(pair<string, vector<string>>(offset, vec));

    this->offset_src.push_back(tempMap);
}

vector<map<string, vector<string>>> VectorAdd::getOffsetSrc() {
    return this->offset_src;
}


vector<string> VectorAdd::searchOffset(string offset) {
    
}

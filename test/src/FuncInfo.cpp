#include "../include/FuncInfo.h"
#include <iostream>
#include <fstream>

FuncInfo::FuncInfo() {
    this->funcName = "";
}

FuncInfo::FuncInfo(string funcName) {
    this->funcName = funcName;
}

FuncInfo::FuncInfo(const FuncInfo &obj) {
    this->funcName = obj.funcName;
//
//    this->srcFileSet = obj.srcFileSet;  //STL中的容器直接赋值是安全的，即是深拷贝; vec1 = vec2,赋值之后，vec1和vec2之间就没有关联了
//
//    this->codeSet = obj.codeSet;
//
//    this->map_offset_src = obj.map_offset_src;

    copy(obj.srcFileSet.begin(),obj.srcFileSet.end(),inserter(this->srcFileSet,this->srcFileSet.begin()));
    copy(obj.codeSet.begin(),obj.codeSet.end(),inserter(this->codeSet,this->codeSet.begin()));
    copy(obj.map_offset_src.begin(),obj.map_offset_src.end(),inserter(this->map_offset_src,this->map_offset_src.begin()));
}

FuncInfo::~FuncInfo() {

}

// Clear
void FuncInfo::clear() {
    this->funcName = "";
    this->srcFileSet.clear();
    this->codeSet.clear();
    this->map_offset_src.clear();
}


// Function Name
void FuncInfo::setFuncName(string funcName) {
    this->funcName = funcName;
    //this->srcFileSet.insert("no src file");
}

string FuncInfo::getFuncName() {
    return this->funcName;
}

// Src File
void FuncInfo::addSrcFile(string filePath, string fileLine) {
    //this->srcFileSet.insert(filePath.append("     Line: ").append(fileLine));
    this->srcFileSet.insert(filePath);
}

set<string> FuncInfo::getSrcFile() {
    return this->srcFileSet;
}

void FuncInfo::addOffsetSrc(int offset, string filePath, string line, string code) {

    this->codeSet.insert(code); // 找找直接返回指针的 set 函数

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
        cout << "Src File Path: " << *iter->second.src_path << "   Line " << iter->second.src_line << endl;
        cout << "Code: " << *iter->second.code << endl;
        return iter->second;
    }

}


// Print
void FuncInfo::printSrcFile() {
    for (auto i = this->srcFileSet.begin(); i != this->srcFileSet.end(); i++)
        cout << *i << endl;
}

void FuncInfo::printOffset() {
//    string s1("../data/printOffset_"), s2(this->funcName), s3(".txt");
//    ofstream outfile("../data/printOffset_");
//    if(!outfile){
//        cout << "Unable to open outfile";
//        exit(1); // terminate with error
//    }

    //map<int, struct OffsetInfo> offset_src = this->getOffsetSrc();
    auto iter = this->map_offset_src.begin();
    while (iter != this->map_offset_src.end()) {
        //cout << this->funcName << endl;
        cout << "Offset: " << iter->first << endl;
        cout << "   Src File: " << *iter->second.src_path << "     Line: " << iter->second.src_line << endl;
        cout << "   Code: " << *iter->second.code << endl << endl;

//        outfile << this->funcName << "\n";
//        outfile << "Offset: " << iter->first << "\n";
//        outfile << "   Src File: " << *iter->second.src_path << "     Line: " << iter->second.src_line << "\n";
//        outfile << "   Code: " << *iter->second.code << "\n" << "\n";

        iter++;
    }

//    outfile.close();
}

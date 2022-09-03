#include <iostream>
#include <string>
#include "mapRes.pb.h"

using namespace std;

void decode(string serializedStr);
string encode();

int main(int argc, char* argv[]) {
    string serializedStr = encode();
/*----------------上面是序列化，下面是反序列化-----------------------*/
    decode(serializedStr);
}

string encode() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    kernel::mapRes maps;

    // * Construct a FuncInfo object
    kernel::mapRes::FuncInfo* FI_1 = maps.add_fi();
    FI_1->set_funcname("func1");
    // ** vector 赋值
    FI_1->add_srcfileset("src1");
    FI_1->add_srcfileset("src2");
    FI_1->add_codeset("code1");
    FI_1->add_codeset("code2");

    // ** construct SASSLineInfo
    kernel::mapRes::FuncInfo::SASSLineInfo* SASSLine_1 = FI_1->add_sassline();
    SASSLine_1->set_src_path("src1");
    SASSLine_1->set_src_line(13);
    SASSLine_1->set_code("code1");

    // *** construct Register
    kernel::mapRes::FuncInfo::SASSLineInfo::Register* reg_GPR = new kernel::mapRes::FuncInfo::SASSLineInfo::Register();
    reg_GPR->set_name("GPR");
    reg_GPR->set_size(255);
    reg_GPR->set_occupied_count(8);
    reg_GPR->add_reg_status(0);
    reg_GPR->add_reg_status(2);

    // ** set SASSLineInfo's reg status
    *SASSLine_1->mutable_reg_gpr() = *reg_GPR;

    // * Push SASSLineInfo into FuncInfo offset map
    auto map_offset_src = FI_1->mutable_map_offset_src();
    (*map_offset_src)[0] = *SASSLine_1;


    // Push FuncInfo into maps
    auto resMap = maps.mutable_testmap();
    (*resMap)[FI_1->funcname()] = *FI_1;





    // 对消息对象student序列化到string容器
    string serializedStr;
    maps.SerializeToString(&serializedStr);
    cout<<"serialization result: "<<serializedStr<<endl; //序列化后的字符串内容是二进制内容，非可打印字符，预计输出乱码
    cout<<endl<<"debugString:"<<maps.DebugString();

    return serializedStr;
}

void decode(string serializedStr) {
    //解析序列化后的消息对象，即反序列化
    kernel::mapRes deserializedMapRes;
    if(!deserializedMapRes.ParseFromString(serializedStr)){
        cerr << "Failed to parse maps." << endl;
        return;
    }

    cout<<"-------------上面是序列化，下面是反序列化---------------"<<endl;
    //打印解析后的student消息对象
    cout<<"deserializedStudent debugString:"<<deserializedMapRes.DebugString();
    cout <<endl<<"Map Results Size: " << deserializedMapRes.testmap().size() << endl;
//    cout <<endl<<"Map Results: " << (deserializedMapRes.testmap())["666"] << endl;

    auto it = deserializedMapRes.testmap().find("func1");
    if (it != deserializedMapRes.testmap().end()) {
        cout << it->second.srcfileset()[0] << endl;
        cout << it->second.srcfileset()[1] << endl;
        cout << it->second.codeset()[0] << endl;
        cout << it->second.codeset()[1] << endl;

        auto it_0 = it->second.map_offset_src().find(0);
        if (it_0 != it->second.map_offset_src().end()) {
            cout << it_0->second.src_path() << " " << it_0->second.src_line() << endl;
            cout << it_0->second.code() << endl;
            cout << it_0->second.reg_gpr().name() << " " << it_0->second.reg_gpr().reg_status()[1] << endl;
            cout << it_0->second.reg_gpr().name() << " " << it_0->second.reg_gpr().size() << endl;
        }
    }


    google::protobuf::ShutdownProtobufLibrary();
}


#include <iostream>
#include <fstream>
#include <regex>
#include "../include/regex_test.h"
#include "../include/FuncInfo.h"
#include "../include/helpFunc.h"
#include "../include/Register.h"
#include "../include/lib.h"

using namespace std;


int main() {

    //init
    //init("../data/castro0.txt");      //写成全局变量    // 声明定义在lib  init外面     init("/castro.txt")  init后 searchOffset
    init("../data/castro.head_10000.txt");
    //init("../data/sass/darknet.3.sm_86.cubin.sass");

    cout << endl << "Count of kernels: " << map_FuncInfos.size() << endl << endl;

//    searchOffset(map_FuncInfos["_ZN3cub11EmptyKernelIvEEvv"], 0);
//    searchOffset(map_FuncInfos["_ZN5amrex13launch_globalILi256EZNS_11ParallelForIiZNS_7BaseFabIiE6setValILNS_5RunOnE1EEEvRKiRKNS_3BoxENS_8DestCompENS_8NumCompsEEUliiiiE_vEENSt9enable_ifIXsr5amrex19MaybeDeviceRunnableIT0_vEE5valueEvE4typeERKNS_3Gpu10KernelInfoESA_T_OSF_EUlvE_EEvSF_"], 64);
//    searchOffset(map_FuncInfos["_ZN5amrex13launch_globalILi256EZNS_11ParallelForIiZNS_7BaseFabIiE6setValILNS_5RunOnE1EEEvRKiRKNS_3BoxENS_8DestCompENS_8NumCompsEEUliiiiE_vEENSt9enable_ifIXsr5amrex19MaybeDeviceRunnableIT0_vEE5valueEvE4typeERKNS_3Gpu10KernelInfoESA_T_OSF_EUlvE_EEvSF_"], 144);
//    searchOffset(map_FuncInfos["_ZN5amrex13launch_globalILi256EZNS_11ParallelForIiZNS_7BaseFabIiE6setValILNS_5RunOnE1EEEvRKiRKNS_3BoxENS_8DestCompENS_8NumCompsEEUliiiiE_vEENSt9enable_ifIXsr5amrex19MaybeDeviceRunnableIT0_vEE5valueEvE4typeERKNS_3Gpu10KernelInfoESA_T_OSF_EUlvE_EEvSF_"], 240);
    return 0;
}



#include <iostream>
#include "../include/FuncInfo.h"
#include "../include/lib.h"

using namespace std;


int main() {

    //init

    //init("../data/castro.head_10000.txt");
    init("/Users/kwok/Documents/2022_Summer/Materials/castro.txt");

//    init("../data/castro1.txt");      //写成全局变量    // 声明定义在lib  init外面     init("/castro.txt")  init后 searchOffset
//    searchOffset(map_FuncInfos["_ZN3cub11EmptyKernelIvEEvv"], 0);
//    searchOffset(map_FuncInfos["_ZN5amrex13launch_globalILi256EZNS_11ParallelForIiZNS_7BaseFabIiE6setValILNS_5RunOnE1EEEvRKiRKNS_3BoxENS_8DestCompENS_8NumCompsEEUliiiiE_vEENSt9enable_ifIXsr5amrex19MaybeDeviceRunnableIT0_vEE5valueEvE4typeERKNS_3Gpu10KernelInfoESA_T_OSF_EUlvE_EEvSF_"], 64);
//    searchOffset(map_FuncInfos["_ZN5amrex13launch_globalILi256EZNS_11ParallelForIiZNS_7BaseFabIiE6setValILNS_5RunOnE1EEEvRKiRKNS_3BoxENS_8DestCompENS_8NumCompsEEUliiiiE_vEENSt9enable_ifIXsr5amrex19MaybeDeviceRunnableIT0_vEE5valueEvE4typeERKNS_3Gpu10KernelInfoESA_T_OSF_EUlvE_EEvSF_"], 144);
//    searchOffset(map_FuncInfos["_ZN5amrex13launch_globalILi256EZNS_11ParallelForIiZNS_7BaseFabIiE6setValILNS_5RunOnE1EEEvRKiRKNS_3BoxENS_8DestCompENS_8NumCompsEEUliiiiE_vEENSt9enable_ifIXsr5amrex19MaybeDeviceRunnableIT0_vEE5valueEvE4typeERKNS_3Gpu10KernelInfoESA_T_OSF_EUlvE_EEvSF_"], 240);


//    init("../data/sass/darknet.1.sm_86.cubin.sass");
//    searchOffset(map_FuncInfos["_Z27assisted_activation2_kernelfPfS_S_iii"], 912);
//    searchOffset(map_FuncInfos["_Z27assisted_activation2_kernelfPfS_S_iii"], 1088);
//    searchOffset(map_FuncInfos["_Z27assisted_activation2_kernelfPfS_S_iii"], 1584);

//    init("../data/sass/darknet.10.sm_86.cubin.sass");
//    searchOffset(map_FuncInfos["_Z28forward_avgpool_layer_kerneliiiiPfS_"], 672);
//    searchOffset(map_FuncInfos["_Z28forward_avgpool_layer_kerneliiiiPfS_"], 928);
//    searchOffset(map_FuncInfos["_Z29backward_avgpool_layer_kerneliiiiPfS_"], 432);

    cout << endl << "Count of kernels: " << map_FuncInfos.size() << endl << endl;

    return 0;
}



#include <iostream>
#include <fstream>

using namespace std;

void func1();

int main() {

    func1();

    return 0;
}

void func1() {
    ifstream myfile ("../data/vectoradd.txt");
    ofstream outfile("../data/result.txt");

    string tempStr;

    if(!myfile){
        cout << "Unable to open myfile";
        exit(1); // terminate with error

    }
    if(!outfile){
        cout << "Unable to open otfile";
        exit(1); // terminate with error

    }

    while (getline(myfile, tempStr)) {

        auto pos1 = tempStr.find("//##");
        if (pos1 != tempStr.npos) {
            outfile << tempStr << "\n\n";
        }


    }


    myfile.close();
    outfile.close();
}
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]){
    cout << "you have entered " << argc << " arguments:" << endl;

    int i = 0;
    while(i < argc){
        cout << "argument " << i+1 << ": " <<argv[i] << endl;
        i++;
    }
    std::ifstream file(argv[2]);
    return 0;
}

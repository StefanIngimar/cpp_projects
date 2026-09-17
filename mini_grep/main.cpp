#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]){

    if(argc != 3){
        cerr << "you have to insert arguments" << endl;
        return 1;
    }
    cout << "you have entered " << argc << " arguments:" << endl;

    int i = 0;
    while(i < argc){
        cout << "argument " << i+1 << ": " <<argv[i] << endl;
        i++;
    }
    string searchTerm = argv[1];
    std::ifstream file(argv[2]);

    cout << "searching for: " << searchTerm << endl;

    string line;
    size_t lineNumber = 0;

    while(getline(file, line)){
        lineNumber++;
        size_t position = line.find(searchTerm);

        if(position != string::npos){
            cout << "Line " << lineNumber
                << ", position " << position
            << ": " << searchTerm << endl;
        }
    }
    return 0;
}

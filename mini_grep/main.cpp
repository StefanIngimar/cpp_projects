#include <iostream>
#include <fstream>
#include <string>
#include "locale"
#include <algorithm>
using namespace std;

template<typename charT>
struct my_equal {
    my_equal( const std::locale& loc ) : loc_(loc) {}
    bool operator()(charT ch1, charT ch2) {
        return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    }
private:
    const std::locale& loc_;
};

// find substring (case insensitive)
template<typename T>
int ci_find_substr( const T& str1, const T& str2, const std::locale& loc = std::locale() )
{
    typename T::const_iterator it = std::search( str1.begin(), str1.end(),
        str2.begin(), str2.end(), my_equal<typename T::value_type>(loc) );
    if ( it != str1.end() ) return it - str1.begin();
    else return -1; // not found
}

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
        size_t position = ci_find_substr(line, searchTerm);

        if(position != -1){
            cout << "Line " << lineNumber
                << ", position " << position
            << ": " << searchTerm << endl;
        }
    }
    return 0;
}

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

void searchFile(const string& filename, const string& searchTerm, bool count){
    // string filename = argv[i];
    ifstream file(filename);

    if (!file) {
        cerr << "Could not open: " << filename << endl;
        // continue;
    }

    string line;
    size_t lineNumber = 0;
    size_t matchCount = 0;

    while (getline(file, line)) {
        lineNumber++;

        int position = ci_find_substr(line, searchTerm);

        if (position != -1) {
            matchCount++;

            if (!count) {
                cout << filename
                     << ":" << lineNumber
                     << ":" << position
                     << ": " << searchTerm << endl;
            }
        }
    }

    if (count) {
        cout << filename << ": " << matchCount << endl;
    }
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cerr << "Usage: minigrep <search-term> <file> [file ...] [--count]" << endl;
        return 1;
    }

    string searchTerm = argv[1];

    bool count = false;

    for (int i = 2; i < argc; i++) {
        if (string(argv[i]) == "--count") {
            count = true;
        }
    }

    for (int i = 2; i < argc; i++) {

        if (string(argv[i]) == "--count") {
            continue;
        }
        searchFile(argv[i], searchTerm, count);
    }
}

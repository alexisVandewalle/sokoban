#include "SokoParser.h"
#include <iostream>

using namespace std;
using namespace soko;

int main(int argc, char**argv){
    if(argc != 4){
        cerr << "Invalid number of arguments" << endl;
        cerr << "you should provide <input file path> <output dir> and <map set title>" << endl;
        return EXIT_FAILURE;
    }
    string inFilePath(argv[1]), outDir(argv[2]), mapSetTitle(argv[3]);
    SokoParser myParser(inFilePath, outDir, mapSetTitle);
    myParser.parse();
    cout << "maps successfuly imported in " << argv[2] << endl; 
    return EXIT_SUCCESS; 
}


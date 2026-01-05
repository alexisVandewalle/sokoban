#include "test.h"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace test;

int test::testSokoban(){
    cout << "Hello world!" << endl;
    return 0; 
}

void test::printHelp(string& progName){
    cout << "This is the program to launch test for the sokoban application" << endl;
    cout << "Usage: " << progName << " testName" << endl;
    cout << endl << "Available tests:" << endl;
}

int main(int argc, char**argv){
    string progName(argv[0]); 
    if(argc != 2){
        printHelp(progName);
        return EXIT_FAILURE;
    }
    string arg(argv[1]);
    if(arg=="--help"){
        printHelp(progName);
        return EXIT_SUCCESS;
    }else if(arg=="testSokoban"){
        cout << "Executing test sokoban..." << endl;
        return testSokoban();
    }else{
        cerr << "Unknown test name" << endl;
        return EXIT_FAILURE;
    } 
        
    return 0;
}

// test.h
#ifndef TEST_H // include guard
#define TEST_H
#include <string>

using namespace std;

namespace test
{
    /**
     * Print help of test exec
     * @param progName name of the exec
     */
    void printHelp(string& progName);

    /**
     * An example test
     */
    int testSokoban();
    
    /**
     * Test loading and saving of given map
     * @param argc number of arguments of the test (including test name)
     * @param argv arguments passed to the test (test name should be the first argument,
     * 2nd arguments is the save location)
     * @return test status
     */
    int testMapLoadSave(int argc, char* argv[]);

    /**
     * Test all possible moves performed on a map
     * @param argc number of arguments of the test (including test name)
     * @param argv arguments passed to the test (test name should be the first argument)
     * @return test status
     */
    int testMapMove(int argc, char* argv[]);
}

#endif /* TEST_H */

// test.h
#ifndef TEST_H // include guard
#define TEST_H
#include <string>

using namespace std;

namespace test
{
    /**Print help of test exec
     * @param progName name of the exec
     */
    void printHelp(string& progName);

    /**
     * An example test
     */
    int testSokoban();

}

#endif /* TEST_H */

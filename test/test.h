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
     * Test a given move on a map (all cases are tested)
     * @param argc number of arguments of the test (including test name)
     * @param argv arguments passed to the test (first argument should be the move to test)
     * @return test status
     */
    int testMapMove(int argc, char* argv[]);

    /**
     * Load a map and launch an interactive game
     */
    int testInteractiveGame(int argc, char* argv[]);

    int testSokoParser(int argc, char* argv[]);

    /**
     * Test copy of a map and hash computation of a map
     */
    int testCopyHashMap(int argc, char* argv[]);

    /**
     * Test the NodeMap class and test that it can be used
     * in an unordered_set
     */
    int testNodeMap(int argc, char* argv[]);

    /**
     * Test sokoban solver given an imput map.
     * The test run the solver and check if solution
     * works applying the moves one by one.
     */
    int testSokobanSolver(int argc, char* argv[]);
}

#endif /* TEST_H */

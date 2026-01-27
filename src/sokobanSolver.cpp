#include "Solver.h"
#include <iostream>
#include "Map.h"

using namespace std;
using namespace soko;

int main(int argc, char**argv){
    if(argc != 2){
        cerr << "Invalid number of arguments" << endl;
        cerr << "you should provide <input map path>" << endl;
        return EXIT_FAILURE;
    }
    Map map(argv[1]);
    cout << "Map to solve:" << endl;
    cout << map.toString() << endl;
    Solver s(map);
    s.run();
    if(s.isSolve()){
        cout << "Solution found to sokoban map" << endl;
        cout << " * solution:" << s.getSolution() << endl;
        cout << " * number of visited nodes:" << s.getNbVisitedNode() << endl;
    }else{
        cout << "No solution found - map impossible to solve" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS; 
}


// Solver.h
#ifndef SOLVER_H // include guard
#define SOLVER_H
#include <string>
#include "NodeMap.h"

using namespace std;

namespace soko
{
    /**
     * An example class that does nothing
     */
    class Solver
    {
        private:
            NodeMap startNode;
            bool mIsSolve;
            string solution;
        public:
            Solver(Map& map);
            void run();
            bool isSolve();
            string getSolution();
    };
}

#endif /* SOLVER_H */

// Solver.h
#ifndef SOLVER_H // include guard
#define SOLVER_H
#include <string>
#include "NodeMap.h"

using namespace std;

namespace soko
{
    /**
     * A class which implements a solver to solve a given sokoban map.
     */
    class Solver
    {
        private:
            NodeMap startNode;
            bool mIsSolve;
            string solution;
        public:
            /**
             * Construct a solver given an input map
             */
            Solver(Map& map);

            /**
             * run the solver a try to find the shortest solution
             */
            void run();

            /** Return true if the solver found a solution
             */
            bool isSolve();

            /** Return solution to the problem
             */
            string getSolution();
    };
}

#endif /* SOLVER_H */

#include "Solver.h"
#include <iostream>
#include <unordered_set>
#include <queue>
#include "MoveType.h"

using namespace std;
using namespace soko;

Solver::Solver(Map& map) : startNode(map), mIsSolve(false){
}

void Solver::run(){
    unordered_set<shared_ptr<NodeMap>, NodeMapHasher, NodeMapKeyEqual> visitedNode;
    queue<shared_ptr<NodeMap>> nodeToVisit;
    vector<MoveType> moves = {LEFT,RIGHT,DOWN,UP};
    shared_ptr<NodeMap> startNodePtr = make_shared<NodeMap>(startNode);
    // init list of nodes to visit
    nodeToVisit.push(startNodePtr);
    if(startNode.isWin()){
        mIsSolve = true;
        solution = "";
        return; 
    }
    for(; !nodeToVisit.empty(); nodeToVisit.pop()){
        for(int i=0; i< moves.size(); i++){
            shared_ptr<NodeMap> nextNode = make_shared<NodeMap>(*nodeToVisit.front(), moves[i]);
            if(nextNode->isWin()){
                mIsSolve = true;
                solution = nextNode->getMoveSeq();
                return;
            }
            if(visitedNode.count(nextNode) == 0){
                visitedNode.insert(nextNode);
                nodeToVisit.push(nextNode);
            }
        }
    }
}

bool Solver::isSolve(){
    return mIsSolve;
}

string Solver::getSolution(){
    return solution;
}

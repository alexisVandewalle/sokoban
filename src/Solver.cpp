#include "Solver.h"
#include <iostream>
#include <unordered_set>
#include <queue>
#include "MoveType.h"

using namespace std;
using namespace soko;

Solver::Solver(Map& map) : mIsSolve(false){
    startNode = make_shared<NodeMap>(map);
}

void Solver::run(){
    unordered_set<shared_ptr<NodeMap>, NodeMapHasher, NodeMapKeyEqual> visitedNode;
    queue<shared_ptr<NodeMap>> nodeToVisit;
    vector<MoveType> moves = {LEFT,RIGHT,DOWN,UP};
    // init list of nodes to visit
    nodeToVisit.push(startNode);
    if(startNode->isWin()){
        nbVisitedNode = visitedNode.size();
        mIsSolve = true;
        solution = "";
        return; 
    }
    for(; !nodeToVisit.empty(); nodeToVisit.pop()){
        for(int i=0; i< moves.size(); i++){
            shared_ptr<NodeMap> nextNode = make_shared<NodeMap>(nodeToVisit.front(), moves[i]);
            if(nextNode->isWin()){
                nbVisitedNode = visitedNode.size();
                mIsSolve = true;
                solution = nextNode->getMoveSeq();
                return;
            }
            if(visitedNode.count(nextNode) == 0 && !nextNode->mapLocked()){
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

long Solver::getNbVisitedNode() const{
    return nbVisitedNode;
}

#include "NodeMap.h"
#include <iostream>

using namespace std;
using namespace soko;

NodeMap::NodeMap(NodeMap& aParent, MoveType m){
    this->parent = &aParent;
    if(parent!=nullptr){
        // create a copy of the parent's map and perform a move
        map = make_unique<Map>(*(parent->map));
        map->move(m);
        move = m;
    }
}

NodeMap::NodeMap(const Map& m){
    // create a copy of the map
    map = make_unique<Map>(m);
    parent = nullptr;
}

NodeMap::NodeMap(const NodeMap& n){
    parent = n.parent;
    map = make_unique<Map>(*(n.map));
    move = n.move;
}

bool NodeMap::operator==(const NodeMap& n2) const {
    return (*(this->map))==(*(n2.map));
}

string NodeMap::getMoveSeq(){
    string out;
    NodeMap* currentNode = this;
    while(currentNode->parent!=nullptr){
        out = static_cast<char>(currentNode->move) + out;
        currentNode = currentNode->parent;
    }
    return out;
}

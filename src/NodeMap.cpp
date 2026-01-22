#include "NodeMap.h"
#include <iostream>

using namespace std;
using namespace soko;

NodeMap::NodeMap(shared_ptr<NodeMap> parent, MoveType m){
    this->parent = parent;
    if(parent!=nullptr){
        map = make_unique<Map>(*(parent->map));
        map->move(m);
    }
}

NodeMap::NodeMap(const Map& m){
    map = make_unique<Map>(m);
}

bool NodeMap::operator==(const NodeMap& n2){
    return (*(this->map))==(*(n2.map));
}

string NodeMap::getMoveSeq(){
    string out;
    while(this->parent!=nullptr){
        out = out + move;
    }
    return out;
}

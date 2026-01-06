#include "Map.h"
#include <iostream>

using namespace std;
using namespace soko;

int Map::getNLines(){
    return nLines;
}

int Map::getNCol(){
    return nCol;
}

int Map::move(MoveType direction){
    return 0;
}

void Map::show(){
}

bool Map::isWin(){
    return false;
}

void Map::save(string filename){
}

Map::Map(string filename){
}

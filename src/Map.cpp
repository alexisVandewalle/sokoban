#include "Map.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace soko;

int Map::getNLines(){
    return nLines;
}

int Map::getNCol(){
    return nCol;
}

int Map::getNTarget(){
    return nTarget;
}

string Map::getTitle(){
    return title;
}

string Map::getOtherMetadata(){
    return otherMetadata;
}
int Map::getNBoxOnTarget(){
    return nBoxOnTarget;
}

vector<int> Map::getCharacterPos(){
    return characterPos;
}

vector<int> Map::getNLineColMap(string filePath){
    ifstream mapFile(filePath);
    vector<int> out(getNLineColMap(mapFile));
    mapFile.close();
    return out;
}

vector<int> Map::getNLineColMap(istream& inStream){
    vector<int> nLineCol = {0,0};
    string line;
    while(getline(inStream, line)){
        // metadata area is separated from map with a line break
        if(line==""){
            break;
        }
        nLineCol[0]++;
        if(line.length() > nLineCol[1]){
            nLineCol[1] = line.length();
        }
    }
    return nLineCol;
}

int Map::move(MoveType direction){
    // define current block, block+1 and block+2
    BlockType nextBlock = map[characterPos[0]*nCol + characterPos[1]];
    int i0 = characterPos[0], i1=i0, i2 = i1;
    int j0 = characterPos[1], j1=j0, j2 = j1;
    switch(direction){
        case UP:
            i1--;
            i2 = i1 - 1;
            break;
        case DOWN:
            i1++;
            i2 = i1 + 1;
            break;
        case LEFT:
            j1--;
            j2 = j1 - 1;
            break;
        case RIGHT:
            j1++;
            j2 = j1 + 1;
            break;
    }
    BlockType b0(map[i0*nCol+j0]);
    BlockType b1(WALL);
    if((i1>=0) && (i1<nLines) && (j1>=0) && (j1<nCol)){
        b1 = map[i1*nCol + j1];
    }
    BlockType b2(WALL);
    if((i2>=0) && (i2<nLines) && (j2>=0) && (j2<nCol)){
        b2 = map[i2*nCol + j2];
    }

    // determine if move is possible and move character
    MoveStatus moveStatus(MOVE_KO);
    switch(b1){
        case WALL:
            moveStatus = MOVE_KO;
            break;
        case FLOOR:
            map[i1*nCol+j1] = CHARACTER;
            if(b0==CHARACTER){
                map[i0*nCol+j0] = FLOOR;
            }else{
                map[i0*nCol+j0] = TARGET;
            }
            moveStatus = MOVE_OK;
            break;
        case BOX:
            if(b2==WALL){
                moveStatus = MOVE_KO;
            }else if(b2==FLOOR){
                // move character
                map[i1*nCol+j1] = CHARACTER;
                if(b0==CHARACTER){
                    map[i0*nCol+j0] = FLOOR;
                }else{
                    map[i0*nCol+j0] = TARGET;
                }
                // move box
                map[i2*nCol+j2] = BOX;
                moveStatus = MOVE_OK;
            }else if(b2==TARGET){
                // move character
                map[i1*nCol+j1] = CHARACTER;
                if(b0==CHARACTER){
                    map[i0*nCol+j0] = FLOOR;
                }else{
                    map[i0*nCol+j0] = TARGET;
                }
                // move box
                map[i2*nCol+j2] = BOX_ON_TARGET;
                nBoxOnTarget++;
                moveStatus = MOVE_OK;
            }else if(b2==BOX){
                moveStatus = MOVE_KO;
            }else if(b2==BOX_ON_TARGET){
                moveStatus = MOVE_KO;
            }
            break;
        case BOX_ON_TARGET:
            if(b2==WALL){
                moveStatus = MOVE_KO;
            }else if(b2==FLOOR){
                // move character
                map[i1*nCol+j1] = CHARACTER_ON_TARGET;
                if(b0==CHARACTER){
                    map[i0*nCol+j0] = FLOOR;
                }else{
                    map[i0*nCol+j0] = TARGET;
                }
                // move box
                map[i2*nCol+j2] = BOX;

                nBoxOnTarget--;
                moveStatus = MOVE_OK;
            }else if(b2==TARGET){
                // move character
                map[i1*nCol+j1] = CHARACTER_ON_TARGET;
                if(b0==CHARACTER){
                    map[i0*nCol+j0] = FLOOR;
                }else{
                    map[i0*nCol+j0] = TARGET;
                }
                // move box
                map[i2*nCol+j2] = BOX_ON_TARGET;
                moveStatus = MOVE_OK;
            }else if(b2==BOX){
                moveStatus = MOVE_KO;
            }else if(b2==BOX_ON_TARGET){
                moveStatus = MOVE_KO;
            }
            break;
        case TARGET:
            map[i1*nCol+j1] = CHARACTER_ON_TARGET;
            if(b0==CHARACTER){
                map[i0*nCol+j0] = FLOOR;
            }else{
                map[i0*nCol+j0] = TARGET;
            }
            moveStatus = MOVE_OK;
            break;

    }
    // update character position
    if(moveStatus==MOVE_OK){
        characterPos[0] = i1;
        characterPos[1] = j1;
    }
    return moveStatus;
}

string Map::toString(){
    string out;
    for(int i=0; i<nLines; i++){
        for(int j=0; j<nCol; j++){
            out += static_cast<char>(map[i*nCol+j]);
        }
        if(i<(nLines-1)){
            out += '\n';
        }
    }
    return out;
}

void Map::show(){
    cout << toString() << endl;
}

bool Map::isWin(){
    return nTarget==nBoxOnTarget;
}

void Map::save(string filePath){
    ofstream fileToSave(filePath);
    // write map
    fileToSave << toString() << endl << endl;
    // write metada
    fileToSave << "title:" << title << endl;
    fileToSave.close();

}

Map::Map(istream& inStream){
    init(inStream);
}

Map::Map(string filePath){
    ifstream mapFile(filePath);
    init(mapFile);
    mapFile.close();
}

void Map::init(istream& inStream){
    // init number of lines and columns
    vector<int> nLineCol(getNLineColMap(inStream));
    // clear since end of the stream can be reached
    // seekg doesn't work in this case
    inStream.clear(); 
    inStream.seekg(0);
    nLines = nLineCol[0];
    nCol = nLineCol[1];
    map.resize(nLines*nCol, WALL);

    // init vector of position
    characterPos.resize(2);

    string line;
    bool metadataArea(false);
    // line index in the file
    int i = 0;
    while(getline(inStream, line)){
        if(line==""){
            metadataArea = true;
        }
        if(metadataArea){
            // handling of metadata section
            int sepPos = line.find(":");
            string metaDataType(line.substr(0, sepPos));
            if(metaDataType=="title"){
                title = line.substr(sepPos+1);
            }else{
                otherMetadata += line + "\n";
            }
        }else{
            // handling map definition
            for(int j=0; j<line.length(); j++){
                BlockType block = static_cast<BlockType>(line[j]);
                map[i*nCol+j] = block;
                // count number of targets and boxes on target
                if(block==BOX_ON_TARGET || block == TARGET || block==CHARACTER_ON_TARGET){
                    nTarget++;
                }
                if(block==BOX_ON_TARGET){
                    nBoxOnTarget++;
                }
                // fill character position
                if(block==CHARACTER || block==CHARACTER_ON_TARGET){
                    characterPos[0] = i;
                    characterPos[1] = j;
                }
            }
        }
        i++;
    }
}

void Map::transpose(){
    int nLinesTmp = nLines;
    nLines = nCol;
    nCol = nLinesTmp;
    int iTmp = characterPos[0];
    characterPos[0] = characterPos[1];
    characterPos[1] = iTmp;
}

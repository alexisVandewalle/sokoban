#include "Game.h"
#include <iostream>
#include <sstream>
#include <unistd.h>

using namespace std;
using namespace soko;

Game::Game(string mapPath, istream* inStream){
    userInput = inStream;
    mapFilePath = mapPath;
    map = unique_ptr<Map>(new Map(mapPath));
    string otherMetadata(map->getOtherMetadata());
    // parse "other metadata"
    stringstream metaSsStream(otherMetadata);
    string line;
    string moveListStr;
    while(getline(metaSsStream, line)){
        int sepPos = line.find(":");
        string metaDataType(line.substr(0, sepPos));
        if(metaDataType=="moves"){
            moveListStr = line.substr(sepPos+1);
        }
    }
    moveSeq.resize(moveListStr.length());
    for(int i=0; i<moveListStr.length(); i++){
        moveSeq[i] = static_cast<MoveType>(moveListStr[i]);  
    }
    isFinished = map->isWin();
}

void Game::gameLoop(){
    string cmd;
    MoveType move;
    int moveStatus;
    while(!exitLoop){
        system("clear");
        map->show();
        cout << "Enter next move:" << endl;
        (*userInput) >> cmd;
        if(cmd.length()==1){
            char moveChr = cmd[0];
            if(moveChr==UP || moveChr==DOWN || moveChr==LEFT || moveChr==RIGHT){
                moveStatus = map->move(static_cast<MoveType>(moveChr));
            }
        }else if(cmd=="menu"){
            gameMenu();
        }
        else{
            cout << "invalid move, valid command enter help to show help" << endl; 
            sleep(1.0);
        }
        
    }
    
}

void Game::nextTurn(){
}

void Game::saveScores(){
}

void Game::saveGame(){
}

void Game::stop(){
}

void Game::gameMenu(){
    system("clear");
    cout << "Game Menu:" << endl << endl;
    cout << "Current Map:" << map->getTitle() << endl << endl;
    cout << "Stats:" << endl;
    cout << "* number of moves: " << moveSeq.size() << endl;
    cout << "* move history: " << string(moveSeq.begin(), moveSeq.end()) << endl; 
    cout << "* duration: " << string(moveSeq.begin(), moveSeq.end()) << endl << endl; 
    cout << endl << "Commands:" << endl;
    cout << "* 1. resume" << endl;
    cout << "* 2. restart" << endl;
    cout << "* 3. save and go back to start menu" << endl;

    string cmd;
    bool validCmd(false);
    while(!validCmd){
        (*userInput) >> cmd; 
        validCmd = true;
        if(cmd=="1"){
        }else if(cmd=="2"){
            moveSeq.clear();
            map = unique_ptr<Map>(new Map(mapFilePath));
            solveDuration = 0.0;
        }else if(cmd=="3"){
            exitLoop = true;
        }else{
            validCmd = false;
        }
    }
}

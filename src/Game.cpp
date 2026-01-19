#include "Game.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;
using namespace soko;

Game::Game(string mapPath){
    init(mapPath);
}

void Game::init(string mapPath){
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
        }else if(metaDataType=="solveDuration"){
            solveDuration = stod(line.substr(sepPos+1));
        }
    }
    moveSeq.resize(moveListStr.length());
    for(int i=0; i<moveListStr.length(); i++){
        moveSeq[i] = static_cast<MoveType>(moveListStr[i]);  
    }
    isWin = map->isWin();
}

void Game::gameLoop(){
    string cmd;
    MoveType move;
    int moveStatus;
    resume();
    while(!exitLoop){
        system("clear");
        map->show();
        cout << "Enter next move or 'menu':" << endl;
        cin >> cmd;
        if(cmd.length()==1){
            char moveChr = cmd[0];
            if(moveChr==UP || moveChr==DOWN || moveChr==LEFT || moveChr==RIGHT){
                moveStatus = map->move(static_cast<MoveType>(moveChr));
                if(moveStatus==MOVE_OK){
                    moveSeq.push_back(static_cast<MoveType>(moveChr));
                    if(map->isWin()){
                        stop = high_resolution_clock::now();
                        auto intervalSec = duration_cast<microseconds>(stop - start);
                        solveDuration += intervalSec.count()/1e6;
                        isWin = true;
                        exitLoop = true;
                    }
                }
            }else{
                cout << "invalid command or move, enter 'menu' to show valid command" << endl; 
                sleep(1.0);
            }
        }else if(cmd=="menu"){
            pause();
            gameMenu();
            resume();
        }
        else{
            cout << "invalid command or move, enter 'menu' to show valid command" << endl; 
            sleep(1.0);
        }
        
    }
    
}

string Game::getScore(){
    string out;
    string moveStr(moveSeq.begin(), moveSeq.end());
    out += map->getTitle() + ",";
    out += to_string(solveDuration) + "," + moveStr + "," + to_string(moveSeq.size());
    return out;
}

void Game::saveGame(){
    string homePath(getenv("HOME"));
    string dirSoko = homePath + "/.soko";
    string cmd = "mkdir -p " + dirSoko;
    system(cmd.c_str());
    mapFilePath = dirSoko + "/sokoCheckpoint.soko";
    ofstream gameFile(mapFilePath);
    map->save(gameFile);
    string moveStr(moveSeq.begin(), moveSeq.end());
    gameFile << "moves:" << moveStr << endl;
    gameFile << "solveDuration:" << solveDuration << " s" << endl;
    gameFile.close();
}

void Game::gameMenu(){
    system("clear");
    cout << "Game Menu:" << endl << endl;
    cout << "Current Map:" << map->getTitle() << endl << endl;
    cout << "Stats:" << endl;
    cout << "* number of moves: " << moveSeq.size() << endl;
    cout << "* move history: " << string(moveSeq.begin(), moveSeq.end()) << endl; 
    cout << "* duration: " << solveDuration << " s" << endl << endl; 
    cout << endl << "Move commands:" << endl;
    cout << "* LEFT: " << static_cast<char>(LEFT)<< endl; 
    cout << "* RIGHT: " << static_cast<char>(RIGHT)<< endl; 
    cout << "* DOWN: " << static_cast<char>(DOWN)<< endl; 
    cout << "* UP: " << static_cast<char>(UP)<< endl; 
    cout << endl << "Menu options:" << endl;
    cout << "* 1. resume" << endl;
    cout << "* 2. restart from last checkpoint" << endl;
    cout << "* 3. save checkpoint" << endl;
    cout << "* 4. quit" << endl;
    cout << endl << "Option selected:" << endl;


    string cmd;
    bool validCmd(false);
    while(!validCmd){
        cin >> cmd; 
        validCmd = true;
        if(cmd=="1"){
        }else if(cmd=="2"){
            restartFromLastCheckpoint();
        }else if(cmd=="3"){
            saveGame();
        }else if(cmd=="4"){
            exitLoop = true;
        }else{
            validCmd = false;
        }
    }
}

void Game::nextTurn(MoveType move){
    int moveStatus = map->move(move);
    if(moveStatus==MOVE_OK){
        moveSeq.push_back(move);
        if(map->isWin()){
            isWin = true;
        }
    }
}

string Game::mapToString(){
    return map->toString();
}

void Game::restartFromLastCheckpoint(){
    moveSeq.clear();
    init(mapFilePath);
}

void Game::pause(){
    stop = high_resolution_clock::now();
    auto intervalSec = duration_cast<microseconds>(stop - start);
    solveDuration += intervalSec.count()/1e6;
}

void Game::resume(){
    start = high_resolution_clock::now();
}

string Game::getMoveSeq(){
    string out(moveSeq.begin(), moveSeq.end());
    return out;
}

int Game::getNMove(){
    return moveSeq.size();
}

double Game::getSolveDuration(){
    return solveDuration;
}

bool Game::getIsWin(){
    return isWin;
}

void Game::saveScore(){
    string homePath(getenv("HOME"));
    string dirSoko = homePath + "/.soko";
    string cmd = "mkdir -p " + dirSoko;
    system(cmd.c_str());
    
    ofstream scoreFile(dirSoko + "/scores.csv", ios_base::app | ios_base::out);
    scoreFile << getScore() << endl;
    scoreFile.close();
}

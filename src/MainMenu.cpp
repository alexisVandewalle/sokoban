#include "MainMenu.h"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace soko;

MainMenu::MainMenu(){
}


void MainMenu::newGame(){
}

void MainMenu::restartGame(){
}

void MainMenu::score(){
}

void MainMenu::mainMenuLoop(){
    string cmd;
    while(true){
        system("clear");
        cout << "Welcolme to sokoban game!" << endl;
        cout << endl << "Options:" << endl;
        cout << "* 1. New game" << endl;
        cout << "* 2. Resume last game" << endl;
        cout << "* 3. Show scores" << endl;
        cout << "* 4. Quit" << endl;
        cout << endl << "Selected option:" << endl;
        cin >> cmd;

        if(cmd == "1"){

        }else if(cmd=="2"){
        }else if(cmd=="3"){
        }else if(cmd=="4"){
        }else{
            cout << "invalid command or move" << endl;
            sleep(1.0);
        }
    }
}

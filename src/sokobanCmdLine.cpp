#include <iostream>
#include <cstdlib>
#include "Game.h"

using namespace std;
using namespace soko;

int main(int argc, char* argv[]){
    string mapPath(argv[1]);
    cout << "Initialize game" << endl;
    Game game(mapPath);
    cout << "Entering game loop:" << endl;
    game.gameLoop();
    if (game.getIsWin()){
        cout << "You win!!!" << endl;
        cout << "Score:" << endl;
        cout << game.getScore() << endl;
    }
    return EXIT_SUCCESS;
}

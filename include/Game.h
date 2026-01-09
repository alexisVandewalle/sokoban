// Game.h
#ifndef GAME_H // include guard
#define GAME_H

#include <vector>
#include <memory>
#include "Map.h"
#include "MoveType.h"

using namespace std;

namespace soko
{
    /**
     * An example class that does nothing
     */
    class Game
    {
        private:
            unique_ptr<Map> map;
            vector<MoveType> moveSeq;
            istream* userInput;
            bool isFinished = false;
            bool isLocked = false;
            bool exitLoop = false;
            string mapFilePath;
            double solveDuration = 0.0;

        public:
            Game(string mapPath, istream* inStream);
            void gameLoop();
            void nextTurn();
            void saveScores();
            void stop();
            void gameMenu();
    };
}

#endif /* GAME_H */

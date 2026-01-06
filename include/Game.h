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
            bool isFinished;
            bool isLocked;
            int nMoves;

        public:
            Game(string mapPath);
            void gameLoop();
            void nextTurn();
            void saveScores();
            void stop();
    };
}

#endif /* GAME_H */

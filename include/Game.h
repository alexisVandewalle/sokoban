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
     * A class to manage loading of a map and all user interactions
     */
    class Game
    {
        private:
            unique_ptr<Map> map;
            vector<MoveType> moveSeq;
            bool isWin = false;
            bool exitLoop = false;
            string mapFilePath;
            double solveDuration = 0.0;

            void init(string mapPath);
        public:
            /**
             * @param mapPath path to the file containing the map
             */
            Game(string mapPath);

            /**
             * Main loop - collect move enter by user and display
             * game menu if requested
             */
            void gameLoop();

            /**
             * return a string containing duration, moves performed by the user
             * and number of possible moves
             */
            string getScore();

            /**
             * Save the current game to the file ~/.soko/sokoCheckPoint.txt
             * This file contains current map, moves performed, solving duration
             * , map title.
             */
            void saveGame();

            /**
             * Display and manage game menu
             */
            void gameMenu();
    };
}

#endif /* GAME_H */

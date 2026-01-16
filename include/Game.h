// Game.h
#ifndef GAME_H // include guard
#define GAME_H

#include <vector>
#include <memory>
#include "Map.h"
#include "MoveType.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

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
            time_point<high_resolution_clock> start;
            time_point<high_resolution_clock> stop;

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
            
            /**
             * perform given move
             */
            void nextTurn(MoveType move);

            /**
             * Get string representation of the map
             */
            string mapToString();

            /**
             * Restart the game from last checkpoint
             */
            void restartFromLastCheckpoint();

            /**
             * pause timer used to count solve duration
             */
            void pause();

            /**
             * Resume timer used to count solve duration
             */
            void resume();

            /**
             * Get sequence of moves already performed as a string sequence
             */
            string getMoveSeq();

            /**
             * Get number of moves
             */
            int getNMove();

            /**
             * Get solve duration of the sokoban
             */
            double getSolveDuration();

            /**
             * Return variable indicating whether sokoban is solved
             */
            bool getIsWin();

            void saveScore();
    };
}

#endif /* GAME_H */

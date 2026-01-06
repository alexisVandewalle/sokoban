// MainMenu.h
#ifndef MAIN_MENU_H // include guard
#define MAIN_MENU_H

#include "Game.h"

namespace soko
{
    /**
     * An example class that does nothing
     */
    class MainMenu
    {
        private:
            unique_ptr<Game> currentGame;
        public:
            MainMenu();
            void newGame();
            void restartGame();
            void score();
            void mainMenuLoop();
    };
}

#endif /* MAIN_MENU_H */

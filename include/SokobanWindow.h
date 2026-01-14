// SokobanWindow.h
#ifndef SOKOBAN_WINDOW_H // include guard
#define SOKOBAN_WINDOW_H

#include "BlockType.h"
#include "Game.h"

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/flowbox.h>
#include <gtkmm/stack.h>
#include <string>
#include <gtkmm/label.h>

#define IMG_SIZE 100

using namespace std;

namespace soko
{
    class SokobanWindow : public Gtk::Window
    {
        private:
            string assetsPath;
            unique_ptr<Game> game;
            bool gamePaused;
            Gtk::Stack containerGame;
            Gtk::Grid pageGame;
            Gtk::Grid pageMenuGame;
            Gtk::Button menuButton;
            Gtk::Button resumeBtn;
            Gtk::Button restartBtn;
            Gtk::Button saveBtn;
            Gtk::Label labelNMove;
            Gtk::Label labelMoveHist;
            Gtk::Label labelDuration;
            Gtk::Grid gridImg;

            /**
             * Function called when a key is pressed
             */
            bool onKeyPressed(guint keyval, guint keycode, Gdk::ModifierType state);

            /**
             * Show game menu
             */
            void showGameMenu();

            /**
             * Show page containing the sokoban puzzle
             */
            void showGame();

            /**
             * Restart game from last saved checkpoint
             */
            void restartGameFromLastCheckpoint();

            /**
             * Save current sokoban and close application
             */
            void saveCheckpoint();
        public:
            /**
             * Create sokoban window taking path to a given map
             */
            SokobanWindow(int argc, char** argv);

            /**
             * Update display of sokoban map
             */
            void updateMap(string map);
    };
}
#endif /* SOKOBAN_WINDOW_H */

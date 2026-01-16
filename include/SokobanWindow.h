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
#include <gtkmm/box.h>
#include <gtkmm/filedialog.h>

#define IMG_SIZE 50

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
            Gtk::Box pageMainMenu;
            Gtk::Grid pageGame;
            Gtk::Grid pageMenuGame;
            Gtk::Button startNewGameBtn;
            Gtk::Button resumeLastGameBtn;
            Gtk::Button showScoreBtn;
            Gtk::Button quitBtn;
            Gtk::Button menuButton;
            Gtk::Button resumeBtn;
            Gtk::Button restartBtn;
            Gtk::Button saveBtn;
            Gtk::Label labelNMove;
            Gtk::Label labelMoveHist;
            Gtk::Label labelDuration;
            unique_ptr<Gtk::Grid> gridImg;
            Glib::RefPtr<Gtk::FileDialog> fileDialog;

            /**
             * Function called when a key is pressed
             */
            bool onKeyPressed(guint keyval, guint keycode, Gdk::ModifierType state);

            /**
             * Show game menu
             */
            void showGameMenu();

            /**
             * Resume exiting game  showing page containing the sokoban puzzle
             */
            void resumeGame();

            /**
             * Restart game from last saved checkpoint
             */
            void restartGameFromLastCheckpoint();

            /**
             * Save current sokoban and close application
             */
            void saveCheckpoint();

            /**
             * Update display of sokoban map
             */
            void updateMap(string map);

            void initGame(string mapPath);
            void exitGame();
            void startNewGame();
            void onMapSelected(Glib::RefPtr<Gio::AsyncResult>& result);
            void resumeLastGame();
            
        public:
            /**
             * Create sokoban window taking path to a given map
             */
            SokobanWindow(int argc, char** argv);

    };
}
#endif /* SOKOBAN_WINDOW_H */

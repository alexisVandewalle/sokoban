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
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/spinbutton.h>
#include "ImportMapDialog.h"

#define IMG_SIZE 50

using namespace std;

namespace soko
{
    class SokobanWindow : public Gtk::Window
    {
        //Tree model columns for scores:
        class ModelColumnsScore : public Gtk::TreeModel::ColumnRecord
        {
            public:

                ModelColumnsScore()
                    { add(colTitle); add(colSolveDuration); add(colNMoves);}

                Gtk::TreeModelColumn<Glib::ustring> colTitle;
                Gtk::TreeModelColumn<Glib::ustring> colSolveDuration;
                Gtk::TreeModelColumn<int> colNMoves;
        };

        private:
            string assetsPath;
            unique_ptr<Game> game;
            bool gamePaused;
            Gtk::Stack containerGame;
            Gtk::Box pageMainMenu;
            Gtk::Box pageGame;
            Gtk::Box pageMenuGame;
            Gtk::Box pageScores;
            Gtk::ScrolledWindow scoreScroller;
            Gtk::Button startNewGameBtn;
            Gtk::Button resumeLastGameBtn;
            Gtk::Button showScoreBtn;
            Gtk::Button importMapsBtn;
            Gtk::Button quitBtn;
            Gtk::Button menuButton;
            Gtk::Button resumeBtn;
            Gtk::Button restartBtn;
            Gtk::Button saveBtn;
            Gtk::Button backToMainMenuBtn;
            Gtk::Label labelNMove;
            Gtk::Label labelMoveHist;
            Gtk::Label labelDuration;
            Gtk::SpinButton imgSizeSpinBtn;
            Gtk::TreeView scoreTreeView;
            Glib::RefPtr<Gtk::ListStore> scoreListStore;
            ModelColumnsScore columnsScore;
            Gtk::Button backBtn;
            unique_ptr<Gtk::Grid> gridImg;
            Glib::RefPtr<Gtk::FileDialog> fileDialog;
            unique_ptr<ImportMapDialog> dialog;

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

            /**
             * construct a new game and show game window
             * @param mapPath path to the map to load
             */
            void initGame(string mapPath);

            /**
             * exit game and show main menu page
             */
            void exitGame();

            /**
             * action performed when clicking on start new game:
             * open a dialog box and ask for the user to choose a map to open.
             * Once done, the map is loaded and the game start
             */
            void startNewGame();
            
            /**
             * When clicking on new game, the function is called to read the map
             * file and init a new game.
             */
            void onMapSelected(Glib::RefPtr<Gio::AsyncResult>& result);

            /**
             * Resume last saved game reading map stored in ~/.soko/sokoCheckpoint.soko
             */
            void resumeLastGame();

            /**
             * Read files containing scores and display it
             */
            void showScores();

            /**
             * Show main menu page.
             */
            void showMainMenu();
            
            /**
             * Open a dialog to import a list of maps
             */
            void importMaps();

            /**
             * Read file containing list of maps to import and import them
             * in selected output directory
             */
            void readAndImport();

        public:
            /**
             * Create sokoban window taking path to a given map
             */
            SokobanWindow(int argc, char** argv);

    };
}
#endif /* SOKOBAN_WINDOW_H */

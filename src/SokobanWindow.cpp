#include "SokobanWindow.h"
#include <gtkmm/image.h>
#include <iostream>
#include <gdk/gdkkeysyms.h>
#include <gtkmm/eventcontrollerkey.h>
#include <gtkmm/error.h>
#include <gtkmm/alertdialog.h>
#include "exceptions.h"
#include <fstream>

using namespace soko;

SokobanWindow::SokobanWindow(int argc, char** argv)
    : pageMainMenu(Gtk::Orientation::VERTICAL, 5),
      pageScores(Gtk::Orientation::VERTICAL, 5)
{
    // path to images (for map display)
    assetsPath = getenv("SOKOBAN_ASSETS");

    // application title
    set_title("Sokoban Application");

    // construct page containing main menu of the game
    startNewGameBtn.set_label("Start new game");
    resumeLastGameBtn.set_label("Resume last saved game");
    showScoreBtn.set_label("Show scores");
    quitBtn.set_label("Quit");
    pageMainMenu.append(startNewGameBtn);
    pageMainMenu.append(resumeLastGameBtn);
    pageMainMenu.append(showScoreBtn);
    pageMainMenu.append(quitBtn);
    pageMainMenu.set_valign(Gtk::Align::CENTER);
    pageMainMenu.set_margin(5);

    // construct page containing sokoban game
    pageGame.attach(menuButton, 0, 1);
    menuButton.set_label("Menu");

    // construct page containg game menu
    pageMenuGame.attach(resumeBtn, 0, 0);
    pageMenuGame.attach(restartBtn, 0, 1);
    pageMenuGame.attach(saveBtn, 0, 2);
    Gtk::Label labelStats("Stats:");
    pageMenuGame.attach(labelStats, 0, 4);
    pageMenuGame.attach(labelNMove, 0, 5);
    pageMenuGame.attach(labelDuration, 0, 6);
    resumeBtn.set_label("Resume");
    restartBtn.set_label("Restart from last checkpoint");
    saveBtn.set_label("Save checkpoint and back to main menu");

    // construct page containing scores
    pageScores.append(scoreScroller);
    scoreScroller.set_child(scoreTreeView);
    scoreScroller.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    scoreScroller.set_expand();
    scoreListStore = Gtk::ListStore::create(columnsScore);
    scoreTreeView.set_model(scoreListStore);
    scoreTreeView.append_column("Map", columnsScore.colTitle);
    scoreTreeView.append_column("Time [s]", columnsScore.colSolveDuration);
    scoreTreeView.append_column("Number of moves", columnsScore.colNMoves);
    backBtn.set_label("Back to main menu");
    pageScores.append(backBtn);

    // add all pages in the window
    containerGame.add(pageMainMenu);
    containerGame.add(pageGame);
    containerGame.add(pageMenuGame);
    containerGame.add(pageScores);
    containerGame.set_visible_child(pageMainMenu);
    set_child(containerGame);
    
    // setting of signals
    startNewGameBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &SokobanWindow::startNewGame));
    resumeLastGameBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &SokobanWindow::resumeLastGame));
    showScoreBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &SokobanWindow::showScores));
    quitBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &SokobanWindow::close));
    menuButton.signal_clicked().connect(
        sigc::mem_fun(*this, &SokobanWindow::showGameMenu));
    resumeBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &SokobanWindow::resumeGame));
    restartBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &SokobanWindow::restartGameFromLastCheckpoint));
    saveBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &SokobanWindow::saveCheckpoint));
    backBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &SokobanWindow::showMainMenu));
    auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(
        sigc::mem_fun(*this, &SokobanWindow::onKeyPressed), false);
    add_controller(controller);

    // create game instance
    if(argc > 1){
        string mapPath(argv[1]);
        initGame(mapPath);
    }
}

void SokobanWindow::initGame(string mapPath){
    game = unique_ptr<Game>(new Game(mapPath));

    // update sokoban map display 
    gridImg = unique_ptr<Gtk::Grid>(new Gtk::Grid);
    pageGame.attach(*gridImg, 0, 0);
    updateMap(game->mapToString());
    gamePaused = false;
    containerGame.set_visible_child(pageGame);

    // start timer used to output the  user score
    game->resume();
}

void SokobanWindow::updateMap(string map){
    if(gridImg == nullptr){
        cout << "no gridImg exists" << endl;
        return;
    }
    int i=0, j=0;
    for(int k=0; k<map.length(); k++){
        if(map[k]!='\n'){
            Gtk::Widget* w = gridImg->get_child_at(j,i);
            if(w==nullptr){
                Gtk::Image img;
                gridImg->attach(img, j, i);
                w = &img;
            }
            w = gridImg->get_child_at(j,i);
            Gtk::Image* img = dynamic_cast<Gtk::Image*>(w);
            img->set_pixel_size(IMG_SIZE);
            switch (map[k]){
                case WALL:
                    img->set(assetsPath + "wall.png");
                    break;
                case CHARACTER:
                    img->set(assetsPath + "character.png");
                    break;
                case CHARACTER_ON_TARGET:
                    img->set(assetsPath + "characterOnTarget.png");
                    break;
                case BOX:
                    img->set(assetsPath + "box.png");
                    break;
                case BOX_ON_TARGET:
                    img->set(assetsPath + "boxOnTarget.png");
                    break;
                case FLOOR:
                    img->set(assetsPath + "ground.png");
                    break;
                case TARGET:
                    img->set(assetsPath + "target.png");
                    break;
            }
            j++;
        }else{
            i++;
            j = 0;
        }
    } 
}

bool SokobanWindow::onKeyPressed(guint keyval, guint keycode, Gdk::ModifierType state){
    if(game==nullptr){
        return false;
    }
    if(!gamePaused){
        if(keyval==GDK_KEY_Up){
            game->nextTurn(UP);
        }else if(keyval==GDK_KEY_Down){
            game->nextTurn(DOWN);
        }else if(keyval==GDK_KEY_Left){
            game->nextTurn(LEFT);
        }else if(keyval==GDK_KEY_Right){
            game->nextTurn(RIGHT);
        }
        if(keyval==GDK_KEY_Up || keyval==GDK_KEY_Down ||keyval==GDK_KEY_Left ||keyval==GDK_KEY_Right){
            if(!game->getIsWin()){
                updateMap(game->mapToString());
            }else{
                game->pause();
                game->saveScore();
                stringstream message;
                message << "You win!!!" << endl;
                message << " * Number of moves: " << game->getNMove() << endl; 
                message << " * Move history: " << game->getMoveSeq() << endl;
                message << " * Solve duration: " << game->getSolveDuration() << "s" << endl;
                cout << message.str();
                Glib::RefPtr<Gtk::AlertDialog> dialog(Gtk::AlertDialog::create(message.str()));
                dialog->show(*this);
                exitGame();
            }
        }
    }
    return false;
}

void SokobanWindow::showGameMenu(){
    gamePaused = true;
    containerGame.set_visible_child(pageMenuGame);
    game->pause();
    labelNMove.set_label("* Number of moves: " + to_string(game->getNMove()));
    labelDuration.set_label("* Solve duration: " + to_string(game->getSolveDuration()));
}

void SokobanWindow::resumeGame(){
    gamePaused = false;
    containerGame.set_visible_child(pageGame);
    game->resume();
}

void SokobanWindow::restartGameFromLastCheckpoint(){
    game->restartFromLastCheckpoint();
    updateMap(game->mapToString());
    resumeGame();
}

void SokobanWindow::saveCheckpoint(){
    game->saveGame();
    exitGame();
}

void SokobanWindow::exitGame(){
    game = nullptr;
    pageGame.remove(*gridImg);
    gridImg = nullptr;
    containerGame.set_visible_child(pageMainMenu);
}

void SokobanWindow::startNewGame(){
    fileDialog = Gtk::FileDialog::create();
    Glib::RefPtr<Gtk::FileFilter> fileFilter(Gtk::FileFilter::create());
    fileFilter->add_pattern("*.soko");
    fileDialog->set_default_filter(fileFilter);
    fileDialog->open(*this,sigc::mem_fun(*this, &SokobanWindow::onMapSelected));
}

void SokobanWindow::onMapSelected(Glib::RefPtr<Gio::AsyncResult>& result){
    Glib::RefPtr<Gio::File> file;
    try{
        file = fileDialog->open_finish(result);
    }
    catch (const Gtk::DialogError& err){
        cout << "No file selected, " << err.what() << endl;
        return;
    }

    string mapPath = file->get_path();
    cout << "Selected file = " << mapPath << endl;
    
    cout << "launching game..." << endl;
    initGame(mapPath);
}

void SokobanWindow::resumeLastGame(){
    string homePath(getenv("HOME"));
    string sokoCheckpointPath(homePath + "/.soko/sokoCheckpoint.soko");
    try{
        initGame(sokoCheckpointPath);
    }catch(FileNotFoundException& e){
        cout << "File " << e.getFilePath() << " not found"<< endl;
        string message("No existing game found!");
        Glib::RefPtr<Gtk::AlertDialog> dialog(Gtk::AlertDialog::create(message));
        dialog->show(*this);
    }
}

void SokobanWindow::showScores(){
    containerGame.set_visible_child(pageScores);
    scoreListStore->clear();
    string homePath(getenv("HOME"));
    string filePathScore(homePath + "/.soko/scores.csv");
    ifstream fileScore(filePathScore);
    if(fileScore.is_open()){
        string line;
        while(getline(fileScore, line)){
            stringstream ss(line);
            string cell;
            // parse map title
            getline(ss, cell, ',');
            auto row = *(scoreListStore->append());
            row[columnsScore.colTitle] = cell;
            //parse solve duration
            getline(ss, cell, ',');
            row[columnsScore.colSolveDuration] = cell;
            // skip move sequence 
            getline(ss, cell, ',');
            // parse nMoves
            getline(ss, cell, ',');
            row[columnsScore.colNMoves] = stoi(cell);
        }
    }
    fileScore.close();
}

void SokobanWindow::showMainMenu(){
    containerGame.set_visible_child(pageMainMenu);    
}

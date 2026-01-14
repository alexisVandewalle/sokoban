#include "SokobanWindow.h"
#include <iostream>
#include <gtkmm/application.h>
#include <unistd.h>

using namespace std;
using namespace soko;

int main(int argc, char**argv){
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    return app->make_window_and_run<SokobanWindow>(0, nullptr, argc, argv);
}

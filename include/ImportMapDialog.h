// ImportMapDialog.h
#ifndef IMPORT_MAP_DIALOG_H// include guard
#define IMPORT_MAP_DIALOG_H

#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/filedialog.h>

using namespace std;

namespace soko
{
    class ImportMapDialog : public Gtk::Window
    {
        private:
            Gtk::Box container;
            Gtk::Entry inputMapListPathEntry;
            Gtk::Entry outputDirEntry;
            Gtk::Entry titleSetEntry;
            Gtk::Button okBtn;
            Glib::RefPtr<Gtk::FileDialog> fileDialog;
            Glib::RefPtr<Gtk::FileDialog> dirDialog;

            string inputMapListPath;
            string outputDir;
            string titleSet;
            sigc::signal<void()> mSignalOkClicked;

        public:
            ImportMapDialog();
            void onOkBtn();
            sigc::signal<void()> signalOkClicked();
            string getSetTitle();
            string getOutputDir();
            string getListFilePath();
            void onInFileSelected(Glib::RefPtr<Gio::AsyncResult>& result);
            void onEntryInFile(Gtk::Entry::IconPosition iconPos);
            void onEntryOutDir(Gtk::Entry::IconPosition iconPos);
            void onOutDirSelected(Glib::RefPtr<Gio::AsyncResult>& result);
    };
}
#endif /* IMPORT_MAP_DIALOG_H */

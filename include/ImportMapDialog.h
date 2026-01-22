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
            /**
             * Dialog window to import a list of sokoban maps
             */
            ImportMapDialog();

            /**
             * Action performed when pressing OK button
             */
            void onOkBtn();

            /**
             * signal emitted when OK button is clicked
             */
            sigc::signal<void()> signalOkClicked();

            /**
             * Return title of the set of maps
             */
            string getSetTitle();

            /**
             * Return output directory path
             */
            string getOutputDir();

            /**
             * Return path to file containing all maps to import
             */
            string getListFilePath();

            /**
             * write path of selected map to entry buffer
             */
            void onInFileSelected(Glib::RefPtr<Gio::AsyncResult>& result);

            /**
             * Action performed when clicking on icon of the entry
             * to select file containing list of maps
             */
            void onEntryInFile(Gtk::Entry::IconPosition iconPos);

            /**
             * Action performed when clicking on icon of the entry
             * to select output directory
             */
            void onEntryOutDir(Gtk::Entry::IconPosition iconPos);

            /**
             * write output directory path to entry buffer to select output
             * directory
             */
            void onOutDirSelected(Glib::RefPtr<Gio::AsyncResult>& result);
    };
}
#endif /* IMPORT_MAP_DIALOG_H */

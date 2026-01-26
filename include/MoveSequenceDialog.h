// MoveSequenceDialog.h
#ifndef MOVE_SEQUENCE_DIALOG_H// include guard
#define MOVE_SEQUENCE_DIALOG_H

#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>

using namespace std;

namespace soko
{
    class MoveSequenceDialog : public Gtk::Window
    {
        private:
            Gtk::Box container;
            Gtk::Entry inputSeqEntry;
            Gtk::Button okBtn;

            sigc::signal<void()> mSignalOkClicked;

        public:
            /**
             * Construct a dialog box requesting a list of moves to perform
             */
            MoveSequenceDialog();

            /**
             * Action performed when pressing OK button
             */
            void onOkBtn();

            /**
             * signal emitted when OK button is clicked
             */
            sigc::signal<void()> signalOkClicked();

            /**
             * Return sequence of moves to be performed
             */
            string getSequence();
    };
}
#endif /* MOVE_SEQUENCE_DIALOG_H */

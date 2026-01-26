#include "MoveSequenceDialog.h"
#include <iostream>
#include <gtkmm/label.h>
#include <gtkmm/button.h>

using namespace std;
using namespace soko;

MoveSequenceDialog::MoveSequenceDialog()
    : container(Gtk::Orientation::VERTICAL, 5)
{
    set_destroy_with_parent(true);
    set_child(container);    
    set_modal(true);

    container.set_margin(5);
    container.set_halign(Gtk::Align::CENTER);
    container.set_valign(Gtk::Align::CENTER);

    // dialog title
    set_title("Sequence of moves to play");

    // add all widgets
    
    // Entry sequence of moves to play
    Gtk::Box sequenceContainer;
    container.append(sequenceContainer);
    Gtk::Label labelSequenceEntry("Sequence of moves to play:");
    sequenceContainer.append(labelSequenceEntry);
    sequenceContainer.append(inputSeqEntry);

    // append ok button
    container.append(okBtn);
    okBtn.set_label("ok");

    // settup signals
    okBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &MoveSequenceDialog::onOkBtn));
}

void MoveSequenceDialog::onOkBtn(){
    mSignalOkClicked.emit();
}

sigc::signal<void()> MoveSequenceDialog::signalOkClicked(){
    return mSignalOkClicked;
}

string MoveSequenceDialog::getSequence(){
    return inputSeqEntry.get_buffer()->get_text();
}


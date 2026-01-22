#include "ImportMapDialog.h"
#include <iostream>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/filedialog.h>
#include <gtkmm/error.h>

using namespace std;
using namespace soko;

ImportMapDialog::ImportMapDialog()
    : container(Gtk::Orientation::VERTICAL, 5)
{
    set_destroy_with_parent(true);
    set_child(container);    
    set_modal(true);

    container.set_margin(5);
    container.set_halign(Gtk::Align::CENTER);
    container.set_valign(Gtk::Align::CENTER);

    // application title
    set_title("Import map dialog");

    // add all widgets
    
    // selector map input file
    Gtk::Box containerInFile;
    container.append(containerInFile);
    Gtk::Label labelInFile("Select input file:");
    containerInFile.append(labelInFile);
    containerInFile.append(inputMapListPathEntry);
    inputMapListPathEntry.set_icon_from_icon_name("document-open");

    // Select path for output directory
    Gtk::Box outputDirContainer;
    container.append(outputDirContainer);
    Gtk::Label labelOutDir("Select path for output directory:");
    outputDirContainer.append(labelOutDir);
    outputDirContainer.append(outputDirEntry);
    outputDirEntry.set_icon_from_icon_name("document-open");

    // Enter title of the set
    Gtk::Box titleSetContainer;
    container.append(titleSetContainer);
    Gtk::Label labelTitleSet("Enter title for the set of maps");
    titleSetContainer.append(labelTitleSet);
    titleSetContainer.append(titleSetEntry);

    // append ok button
    container.append(okBtn);
    okBtn.set_label("ok");

    // settup signals
    okBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &ImportMapDialog::onOkBtn));
    inputMapListPathEntry.signal_icon_press().connect(
        sigc::mem_fun(*this, &ImportMapDialog::onEntryInFile));
    outputDirEntry.signal_icon_press().connect(
        sigc::mem_fun(*this, &ImportMapDialog::onEntryOutDir));
}

void ImportMapDialog::onOkBtn(){
    mSignalOkClicked.emit();
}

sigc::signal<void()> ImportMapDialog::signalOkClicked(){
    return mSignalOkClicked;
}

string ImportMapDialog::getSetTitle(){
    return titleSetEntry.get_buffer()->get_text();
}

string ImportMapDialog::getOutputDir(){
    return outputDirEntry.get_buffer()->get_text();
}

string ImportMapDialog::getListFilePath(){
    return inputMapListPathEntry.get_buffer()->get_text();
}

void ImportMapDialog::onEntryInFile(Gtk::Entry::IconPosition iconPos){
    fileDialog = Gtk::FileDialog::create();
    fileDialog->open(*this,sigc::mem_fun(*this, &ImportMapDialog::onInFileSelected));
}

void ImportMapDialog::onInFileSelected(Glib::RefPtr<Gio::AsyncResult>& result){
    Glib::RefPtr<Gio::File> file;
    try{
        file = fileDialog->open_finish(result);
    }
    catch (const Gtk::DialogError& err){
        cout << "No file selected, " << err.what() << endl;
        return;
    }

    Glib::RefPtr<Gtk::EntryBuffer> entryBuffer = Gtk::EntryBuffer::create(file->get_path());
    inputMapListPathEntry.set_buffer(entryBuffer);
}


void ImportMapDialog::onEntryOutDir(Gtk::Entry::IconPosition iconPos){
    dirDialog = Gtk::FileDialog::create();

    dirDialog->select_folder(*this,sigc::mem_fun(*this, &ImportMapDialog::onOutDirSelected));
}

void ImportMapDialog::onOutDirSelected(Glib::RefPtr<Gio::AsyncResult>& result){
    Glib::RefPtr<Gio::File> dir;
    try{
        dir = dirDialog->select_folder_finish(result);
    }
    catch (const Gtk::DialogError& err){
        cout << "No directory selected, " << err.what() << endl;
        return;
    }

    Glib::RefPtr<Gtk::EntryBuffer> entryBuffer = Gtk::EntryBuffer::create(dir->get_path());
    outputDirEntry.set_buffer(entryBuffer);
}

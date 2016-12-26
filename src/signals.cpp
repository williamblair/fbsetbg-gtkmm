/*
 * signals.cpp - contains signal handler
 * functions as specified in setbgapp.h
 *
 * */

#include "setbgapp.h"

void SetBGApp::setbg_button_clicked(void)
{
	std::cout << "Set BG Button Clicked!\n";

	/* get active file selected */
	std::vector<Gtk::TreePath> activeFiles = iv.get_selected_items();

	if( !activeFiles.empty() )
	{
		/* get path from first selected file */
		Gtk::TreePath path = activeFiles[0];

		/* get iterator */
		Gtk::TreeModel::iterator i = fileListStore->get_iter(path);

		/* get row from iterator */
		Gtk::TreeModel::Row row = *i;

		/* get info from row */
		std::string file = row[imc.filename];

		/* finally run fbsetbg */
		setBackground(file);

	}
	else
		std::cout << "No files selected!\n";


	return;
}

void SetBGApp::addir_button_clicked(void)
{
	std::cout << "Add Directory Button Clicked!\n";

	/* create the initial dialog, using it for
	 * folder selection */
	Gtk::FileChooserDialog d("Select an image folder",
	                       Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	d.set_transient_for(*this);

	/* add buttons to the dialog */
	d.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	d.add_button("Select", Gtk::RESPONSE_OK);

	/* contains the response of the dialog */
	int result = d.run();

	/* handle response */
	switch( result )
	{
		case (Gtk::RESPONSE_OK):
			std::cout << "Folder selected: " << d.get_filename() <<
			                                    std::endl;
			readDir(d.get_filename());
			break;
		case (Gtk::RESPONSE_CANCEL):
			std::cout << "Canceled!\n";
			break;
		default:
			std::cout << "Unexpected button confirmed!\n";
			break;
	}

	return;
}

/* opens the rc file with the system's default text editor */
void SetBGApp::editdir_button_clicked(void)
{	
	/* Is there a better way to do this ??? */
	std::string command = "xdg-open ";
	command += Glib::get_home_dir();
	command += "/" + RC_FILE_STR + " &";
	system(command.c_str());
	return;
}

void SetBGApp::iconview_item_activated(const Gtk::TreeModel::Path &path)
{

	std::cout << "Item Activated!\n";

	/* get iterator */
	Gtk::TreeModel::iterator i = fileListStore->get_iter(path);

	/* get row from iterator */
	Gtk::TreeModel::Row row = *i;

	/* get info from row */
	std::string file = row[imc.filename];

	// DEBUG
	std::cout << "Selected Image: " << file << std::endl;

	/* run the background command */
	setBackground(file);

	return;
}


void SetBGApp::rbf_clicked(void)
{
	if( rbf.get_active() ) {
		option = "-f";
		std::cout << "Using option " << option << std::endl;
	}

	return;
}

void SetBGApp::rbc_clicked(void)
{
	if( rbc.get_active() ) {
		option = "-c";
		std::cout << "Using option " << option << std::endl;
	}

	return;
}

void SetBGApp::rbt_clicked(void)
{
	if( rbt.get_active() ) {
		option = "-t";
		std::cout << "Using option " << option << std::endl;
	}

	return;
}

void SetBGApp::rba_clicked(void)
{
	if( rba.get_active() ) {
		option = "-a";
		std::cout << "Using option " << option << std::endl;
	}

	return;
}


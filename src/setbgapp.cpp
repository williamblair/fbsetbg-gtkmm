
#include <iostream>
#include "setbgapp.h"

SetBGApp::SetBGApp(int argc, char *argv[])
: setbg_button("Set Background"), // create button with label
	addir_button("Add Directory"),
	editdir_button("Edit Directory List"),
	quit_button("Quit"),
	vbox(  Gtk::ORIENTATION_VERTICAL,   0), // create a vbox
	hbox_t(Gtk::ORIENTATION_HORIZONTAL, 0), // hbox for top row
	hbox_b(Gtk::ORIENTATION_HORIZONTAL, 0), // create hbox for bottom row
	hbox_r(Gtk::ORIENTATION_HORIZONTAL, 0), // hbox for options row
	file_counter(0),                        // set file_counter to 0
	rcfile_edited(false),                   // set the rc edited flag to 0
	directory_added(false),                 // set the rc added floder flag to 0
	rbf("Fullscreen"),
	rbc("Centered"),
	rbt("Tiled"),
	rba("Aspect"),
	option("-f")
{
///////////////////////////////////////////////////////////
//               SET WIDGET PROPERTIES                   //
///////////////////////////////////////////////////////////
	/* set border width */
	/* window.set_border_width*/
	set_border_width(10);

	/* default window size */
	set_default_size(400, 400);

	/* initialize scrolled window */
	sw.set_border_width(10);

	/* tell gtk to always show the scroll bars */
	/* first arg - horizontal scrollbar,
	 * second arg - vertical scrollbar */
	sw.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);


	/* make the radio buttons part of the same group */
	Gtk::RadioButton::Group group = rbf.get_group();
	rbc.set_group(group);
	rbt.set_group(group);
	rba.set_group(group);

///////////////////////////////////////////////////////////

	/* Initialize the image list */
	fileListStore = Gtk::ListStore::create(imc);


	/* test directory scanning */
	if( argc == 2 ){
		/* scan the supplied directory for images */
		readDir(argv[1]);
	}
	/* read from last group of used directories */
	else {
		/* read directory here */
		std::string homedir = Glib::get_home_dir();
		
		/* read dir file if it exists */
		std::ifstream f;
		f.open(homedir + "/" + RC_FILE_STR);

		/* check for failure */
		if( !f.is_open() ){
			std::cout << "Error opening rc file: " << homedir + "/" +
			RC_FILE_STR << std::endl;
			std::cout << "Don't worry; I'll create one for you on exit :)\n";
		}
		else{
			/* read in directories */
			char dirname[256];
			std::string dirname_glib;
			while( !f.eof() ){
				f.getline(dirname, 256);
				dirname_glib = dirname;
			
				/* ignore comments */
				if(dirname_glib[0] != '#' && !dirname_glib.empty()) {
					std::cout << "Scanning directory: " << dirname_glib << 
						std::endl;
					readDir(dirname_glib);
				}

			}
			f.close();
		}

	}

	/* add the image list to the icon view */
	iv.set_model(fileListStore);
	iv.set_pixbuf_column(imc.thumbnail);

///////////////////////////////////////////////////////////
//               CONNECT SIGNALS                         //
///////////////////////////////////////////////////////////

	/* SIGNAL FUNCTIONS REFERENCED HERE ARE LOCATED IN 
	 * signals.cpp
	 *
	 * */

	editdir_button.signal_clicked().connect(sigc::mem_fun(*this,
	                              &SetBGApp::editdir_button_clicked));

	setbg_button.signal_clicked().connect(sigc::mem_fun(*this,
	                           &SetBGApp::setbg_button_clicked));

	addir_button.signal_clicked().connect(sigc::mem_fun(*this,
				                     &SetBGApp::addir_button_clicked));

	quit_button.signal_clicked().connect(sigc::mem_fun(*this,
				                     &SetBGApp::close));


	/* icon view signal */
	iv.signal_item_activated().connect(sigc::mem_fun(*this,
	                                   &SetBGApp::iconview_item_activated));

	/* radio button signals */
	rbf.signal_toggled().connect(sigc::mem_fun(*this,
	                             &SetBGApp::rbf_clicked));
	rbc.signal_toggled().connect(sigc::mem_fun(*this,
	                             &SetBGApp::rbc_clicked));
	rbt.signal_toggled().connect(sigc::mem_fun(*this,
	                             &SetBGApp::rbt_clicked));
	rba.signal_toggled().connect(sigc::mem_fun(*this,
	                             &SetBGApp::rba_clicked));

///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
//                  PACK WIDGETS                         //
///////////////////////////////////////////////////////////

	/* add stuff to the top row */
	hbox_t.pack_start(editdir_button, false, false, 0);

	/* add stuff to the options row */
	hbox_r.pack_start(rbf, false, false, 0);
	hbox_r.pack_start(rbc, false, false, 0);
	hbox_r.pack_start(rbt, false, false, 0);
	hbox_r.pack_start(rba, false, false, 0);

	/* add stuff to the bottom button row */
	hbox_b.pack_end(setbg_button, false, false, 0);
	hbox_b.pack_end(addir_button, false, false, 0);
	hbox_b.pack_end(editdir_button, false, false, 0);
	hbox_b.pack_start(quit_button, false, false, 0);

	/* add the icon view to the scroll window */
	sw.add(iv);

	/* add stuff to the vbox */
	vbox.pack_start(hbox_t, false, false, 0);
	vbox.pack_start(sw,      true,  true, 0);
	vbox.pack_start(hbox_r, false, false, 0);
	vbox.pack_start(hbox_b, false, false, 0);


	/* add the vbox to the window */
	/* window.add */
	add(vbox);

///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
//                  UPDATE WIDGETS                       //
///////////////////////////////////////////////////////////
	/* update the widgets */
	setbg_button.show();
	addir_button.show();
	editdir_button.show();
	//editdir_button.show();
	quit_button.show();
	rbf.show();
	rbc.show();
	rbt.show();
	rba.show();
	hbox_b.show();
	hbox_r.show();
	hbox_t.show();
	sw.show();
	iv.show();
	vbox.show();
///////////////////////////////////////////////////////////

} // end of constructor

/* update the rc file with any added folders */
SetBGApp::~SetBGApp(){
	std::cout << "Exiting!\n";

	/* if the user clicked 'edit directory list', skip this section
	 * so the rcfile isn't overwritten 
	 * or if there wasn't a directory added to the current list,
	 * don't bother re-writing */
	if( !rcfile_edited && directory_added )
	{
	std::string homedir = Glib::get_home_dir();
	std::ofstream f;
	/* add ios::trunc to overwrite contents */
	f.open(homedir + "/" + RC_FILE_STR, std::ios::out | std::ios::trunc);
	if( !f.is_open() ){
		std::cout << "File isn't opened on close!\n";
		std::cout << "Skipping...\n";
	}
	else{
		f << "# Generated by fbsetbg-gtkmm at closing based on\n";
		f << "# the current directories searched\n";
		f << "#\n";
		f << "# You can add more directories to scan by adding\n";
		f << "# them to this file\n";
		for(int i=0; i<dir_list.size(); i++){
			f << dir_list[i] << std::endl;
		}
		f.close();
	}
	}
	else {
		if( rcfile_edited) {
			std::cout << "RC File was edited prior to closing," << std::endl;
			std::cout << "Not overwriting!\n";
		}
		else if( !directory_added ){
			std::cout << "No new directories to add, not bothering to overwrite rc file\n";
		}
	}
}

void SetBGApp::AddImageFile(std::string f)
{
	/* new row and iterator for the gtk file list */
	Gtk::TreeModel::iterator i = fileListStore->append();
	Gtk::TreeModel::Row row = *i;

	/* add the filename to the new 'imc_new' */
	row[imc.filename] = f;

	/* create a Gdk::Pixbuf from the given file name 
	 * the false is wether to preserve image aspect or not
	 * */
	row[imc.thumbnail] = Gdk::Pixbuf::create_from_file(f, ICON_WIDTH, 
	                                                      ICON_HEIGHT,
	                                                      false	);

	file_counter++;

	return;
}

void SetBGApp::printFileList(void)
{
	/* contains all of the fileList's children */
	Gtk::TreeModel::Children children = fileListStore->children();

	/* an iterator through the children object */
	Gtk::TreeModel::Children::iterator iter;

	int i=0; // just to print out the number of files

	/* starts at beginning at list until reaches end */
	for( iter=children.begin(), i=0; iter!=children.end(); ++iter, i++)
	{
		Gtk::TreeModel::Row row = *iter; // access data from the current row

		std::cout << "File Name " << i+1 << ":\t" << (std::string)row[imc.filename] << 
		                                              std::endl;
		//std::cout << "File Name:\t" << (std::string)row[imc.filename] << std::endl;
	}

	return;
}


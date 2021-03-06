
#ifndef SET_BG_APP_H
#define SET_BG_APP_H 

/* gtkmm includes */
#include <gtkmm/button.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/iconview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/radiobutton.h>

#include <glibmm/convert.h>

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

/* for directory reading - scan for images */
#include <glibmm/fileutils.h>
#include <glibmm/utility.h>
#include <glibmm/miscutils.h>

/* class for the column record model
 * (needed by the list store, which is
 * needed by the icon view)
 * */
class IconModelColumns : public Gtk::TreeModelColumnRecord
{
	public:
		IconModelColumns(){
			add(filename);
			add(thumbnail);
		}

		Gtk::TreeModelColumn<std::string> filename;
		Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> thumbnail;
};

/* main class for the application */
class SetBGApp : public Gtk::Window
{
	public:
		SetBGApp(int argc, char *argv[]); // constructor
		virtual ~SetBGApp(); // deconstructor

		void AddImageFile(std::string f); // add a file path to the image list
		void printFileList(void); // print out the list

		bool readDir(std::string dir); // scan the given directory for images
		                                   // and add them to the file list vector

		void setBackground(std::string file); // run the fbsetbg command with
		                                        // given file

	protected:

		const int ICON_WIDTH  = 100; // size of the image icons
		const int ICON_HEIGHT = 100;

		/* SIGNAL HANDLERS */
		void setbg_button_clicked();     // set background button handler 
		void addir_button_clicked();     // set add dir button handler
		void editdir_button_clicked();   // set add dir button handler

		void rbf_clicked(); // change option to -f
		void rbc_clicked(); // change option to -c
		void rbt_clicked(); // change option to -t
		void rba_clicked(); // change option to -a

		/* when an icon is selected in the icon view */
		void iconview_item_activated(const Gtk::TreeModel::Path &path);

		/* WIDGETS */
		Gtk::Box    vbox;           // vertical container
		Gtk::Box    hbox_t;         // top vbox for editing search directories
		Gtk::Box    hbox_b;         // holds the bottom row of buttons
		Gtk::Box    hbox_r;         // holds radio buttons
		Gtk::Button setbg_button;   // button to set background
		Gtk::Button addir_button;   // button to add image directory
		Gtk::Button editdir_button; // button to edit the image list file
		Gtk::Button quit_button;    // button to exit the application	
		Gtk::ScrolledWindow sw;     // scroll window

		Gtk::RadioButton rbf, rbc, rbt, rba; // radio buttons for apsect settings
		                                     // -f - fullscreen
		                                     // -c - centered
																				 // -t - tiled
																				 // -a - maximized preserving aspect
		std::string option; // option to be changed by above radio buttons

		Gtk::IconView iv;          // contains image thumbnails for selection

		/* GTK TREE DATA */
		IconModelColumns imc; // instance of the icon store class
		Glib::RefPtr<Gtk::ListStore> fileListStore; // a list store of each image info

		/* FILE DATA */
		int  file_counter;                 // keeps track of how many files we have
		bool rcfile_edited;                // prevents the rc file from being overwritten on close if edited
		bool directory_added;              // tells the program to update the rc file if a folder was added
		std::vector<std::string> dir_list; // keeps track of scanned directories to make
		                                   // sure we don't add multiples of the same image
		const std::string RC_FILE_STR = ".fbsetbg-gtkmm-dirlist";
};

#endif


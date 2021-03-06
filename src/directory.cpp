/*
 * directory.cpp - implementation of the readDir function
 *
 * */

#include "setbgapp.h"

/*
 * Scans the given directory for images
 * and adds them to the file list vector
 * */
bool SetBGApp::readDir(std::string dir)
{
	try {

		/* check if directories list already contains this entry 
		 * returns true if the search reaches the end of the list */
		if( std::find(dir_list.begin(), dir_list.end(), dir) == dir_list.end() )
		{
			/* add the directory to the searched list */
			dir_list.push_back(dir);

			/* create a glib directory object from the given string */
			Glib::Dir d(dir);
			std::vector<std::string> entries(d.begin(), d.end());

			/* make sure directory ends in a '/' so we can append
			 * the image name */
			if(dir[dir.size()-1] != '/') dir += '/';

			if( !entries.empty() )
			{
				for(int i=0; i<entries.size(); i++)
				{
					/* check for image extensions
		 			* TODO - use mimetypes?
		 			* */
					if(	entries[i].find(".png") != std::string::npos || 
							entries[i].find(".PNG") != std::string::npos ||
							entries[i].find(".jpg") != std::string::npos ||
							entries[i].find(".JPG") != std::string::npos ||
							entries[i].find(".jpeg") != std::string::npos ||
							entries[i].find(".JPEG") != std::string::npos 
						)
					{
						/* if the image contains a valid extenstion, add it
 	 		 			 * to the master list
			 			 * TODO - check if image is already on the list
			 			 * */
						AddImageFile(dir + entries[i]);
						std::cout << "Added image \'" << entries[i] << "\'\n";
					}
					else
						std::cout << "Skipping \'" << entries[i] << 
				  	      "\': doesn't match current image extensions!\n";
				}
			}
		}else{
			std::cout << "Already searched directory: " << dir << std::endl;
		}
	}
	catch(Glib::FileError &e){
		std::cerr << "File Exception Error: " << e.what() << std::endl;
		return false;
	}
	catch(Glib::ConvertError &e){
		std::cerr << "Convert Error with Glib: " << e.what() << std::endl;
		return false;
	}

	return true;
}


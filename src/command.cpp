/*
 * command.cpp - function to call the
 * fbsetbg command with a given image name
 * 
 * */

#include "setbgapp.h"

void SetBGApp::setBackground(std::string file)
{
	std::string command = "fbsetbg ";

	/* add scaling options (-f, etc) */
	command += option + " ";

	/* add starting quotation around the file name */
	command += "\'";

	/* add the file name */
	command += file;

	/* add the closing quotation */
	command += "\'";

	/* show the user the command */
	std::cout << "Executing command: " << command << std::endl;

	/* execute the command */
	system(command.c_str());

	return;

}



#include "setbgapp.h"
#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
	/* creates an app
	 * args - argc, argv, char *app id,
	 * 
	 * gtkmm wants to handle arguments, by doing this
	 * workaround we can handle the arguments ourselves
	 * basically tells gtk that there aren't any
	 * arguments, even though there are
	 *  
	 * */
	int arg_copy = argc;
	argc = 1;
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.fbsetbg-gtkmm");

	SetBGApp a(arg_copy, argv);       // instance of our class
	return app->run(a); // shows the window and return when closed
}


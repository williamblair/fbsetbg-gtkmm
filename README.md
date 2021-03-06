# fbsetbg-gtkmm
fbsetbg-gtkmm - frontend for fbsetbg, the fluxbox background setter
William (BJ) Blair III
10/04/16

BASIC INFO:
-------------------
Add images to choose from by pressing the 'Add Directory' button.
You can also set fbsetbg options by selecting from Fullscreen, Centered,
Tiled, and Aspect; which represent the -f, -c, -t, and -a options
respectively. You can either double click on an image to set it
or press the 'Set Background' button. An rc file is stored in
~/.fbsetbg-gtkmm-dirlist, and you can add directories to get images
from in there.

FBSETBG ERRORS:
---------------------------
On Archlinux, fbsetbg gave me a couple of errors at first:
xmessage: command not found  <-- solution: install xorg-xmessage

And, because fbsetbg is a wrapper, you need one of fluxbox's
supported tools to actually set the wallpaper; it suggests installing
esetroot, feh, or wmsetbg. Since feh is the only one of these
currently contained in Arch's repos, install that and you should
be fine.

RUNNING IN FLUXBOX:
----------------------------------
I personally made a directory ~/.fluxbox/applications (not
to be confused with the 'apps' file), and copied the binary there,
then added it to my menu file; but you could run the program from anywhere

To add it to your menu, create an entry similar to this somewhere
in ~/.fluxbox/menu:

	...
	[exec] (Change Background) {/PATH/TO/BINARY} </path/to/icon>
	...

That's it!

COMPILING:
-------------------
to compile fbsetbg-gtk yourself, you will need g++, make, and gtk3
these can be installed on Debian/Ubuntu-ish systems with:

	sudo apt-get install g++
	sudo apt-get install make
	sudo apt-get install libgtkmm-3.0-dev
	sudo apt-get install libatspi2.0-dev
	sudo ldconfig

then compile with:

	make

In the directory you're reading this README from
This will result in a binary in this same root directory

Enjoy! :)

This software is licensed under the GNU GPL, which can be read
in the file COPYING in this current directory.


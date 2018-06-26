
Debian
====================
This directory contains files used to package deviantd/deviant-qt
for Debian-based Linux systems. If you compile deviantd/deviant-qt yourself, there are some useful files here.

## deviant: URI support ##


deviant-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install deviant-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your deviantqt binary to `/usr/bin`
and the `../../share/pixmaps/deviant128.png` to `/usr/share/pixmaps`

deviant-qt.protocol (KDE)


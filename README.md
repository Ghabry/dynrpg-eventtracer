DynRPG Event Tracer
===================

Download unofficial dynrpg from here:

* http://www.rewking.com/dynrpg/

Download a windows build of mingw. It must be i686 (win32) sjlj version.

Minimum gcc 4.7.1 required

* https://sourceforge.net/projects/mingwbuilds/

Create local.mk with

* DYNRPG= location of dynrpg sdk
* CXX= path to mingw g++.exe
* DESTDIR= path to DynPlugins for your game, to use make install


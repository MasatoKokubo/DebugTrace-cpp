@echo off
xcopy        src\DebugTrace.hpp    C:\Library  /DFRY
xcopy      Debug\DebugTrace\*.lib  C:\Library  /DFRY
xcopy  x64\Debug\DebugTrace\*.lib  C:\Library  /DFRY

attrib  +r  C:\Library\*.hpp
attrib  +r  C:\Library\*.lib

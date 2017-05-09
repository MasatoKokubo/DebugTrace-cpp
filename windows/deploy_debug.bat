@echo off
xcopy src\DebugTrace.hpp                  C:\Library     /DFRY
xcopy     Debug\DebugTrace\DebugTrace.lib C:\Library\x86 /DFRY
xcopy x64\Debug\DebugTrace\DebugTrace.lib C:\Library\x64 /DFRY

attrib +r C:\Library\DebugTrace.hpp
attrib +r C:\Library\x86\DebugTrace.lib
attrib +r C:\Library\x64\DebugTrace.lib

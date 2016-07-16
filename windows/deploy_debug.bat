@echo off
xcopy src\DebugTrace.hpp                  C:\Library     /DFY
xcopy     Debug\DebugTrace\DebugTrace.lib C:\Library\x86 /DFY
xcopy x64\Debug\DebugTrace\DebugTrace.lib C:\Library\x64 /DFY
xcopy ARM\Debug\DebugTrace\DebugTrace.lib C:\Library\ARM /DFY

@echo off

copy /Y src\DebugTrace.hpp C:\Library
copy /Y     Debug\DebugTrace\DebugTrace.lib C:\Library\x86
copy /Y x64\Debug\DebugTrace\DebugTrace.lib C:\Library\x64
copy /Y ARM\Debug\DebugTrace\DebugTrace.lib C:\Library\ARM

REM pause

@echo off
setlocal
	set WINDOWS_SRC=windows\src
	set LINUX_SRC=linux

	xcopy %WINDOWS_SRC%\DebugTrace.?pp %LINUX_SRC% /DFY

	xcopy %LINUX_SRC%\DebugTrace.?pp %WINDOWS_SRC% /DFY
endlocal

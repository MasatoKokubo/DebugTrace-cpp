@echo off
setlocal
	set LINUX_SRC=linux
	set MACOS_SRC=macos\src
	set WINDOWS_SRC=windows\src

	xcopy %LINUX_SRC%\DebugTrace.?pp %MACOS_SRC% /DFY
	xcopy %LINUX_SRC%\DebugTrace.?pp %WINDOWS_SRC% /DFY

	xcopy %MACOS_SRC%\DebugTrace.?pp %LINUX_SRC% /DFY
	xcopy %MACOS_SRC%\DebugTrace.?pp %WINDOWS_SRC% /DFY

	xcopy %WINDOWS_SRC%\DebugTrace.?pp %LINUX_SRC% /DFY
	xcopy %WINDOWS_SRC%\DebugTrace.?pp %MACOS_SRC% /DFY

endlocal

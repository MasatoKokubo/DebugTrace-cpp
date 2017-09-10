@echo off
setlocal
	set LINUX_SRC=linux\src
	set MACOS_SRC=macos\src
	set WINDOWS_SRC=windows\src

	xcopy %LINUX_SRC%\Example*.?pp %MACOS_SRC% /DFY
	xcopy %LINUX_SRC%\Example*.?pp %WINDOWS_SRC% /DFY

	xcopy %MACOS_SRC%\Example*.?pp %LINUX_SRC% /DFY
	xcopy %MACOS_SRC%\Example*.?pp %WINDOWS_SRC% /DFY

	xcopy %WINDOWS_SRC%\Example*.?pp %LINUX_SRC% /DFY
	xcopy %WINDOWS_SRC%\Example*.?pp %MACOS_SRC% /DFY

endlocal

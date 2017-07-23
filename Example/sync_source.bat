@echo off
setlocal
	set CENTOS_SRC=centos\src
	set LINUX_SRC=linux\src
	set MACOS_SRC=macos\src
	set WINDOWS_SRC=windows\src

	xcopy %CENTOS_SRC%\Example*.?pp %LINUX_SRC% /DFY
	xcopy %CENTOS_SRC%\Example*.?pp %MACOS_SRC% /DFY
	xcopy %CENTOS_SRC%\Example*.?pp %WINDOWS_SRC% /DFY

	xcopy %LINUX_SRC%\Example*.?pp %CENTOS_SRC% /DFY
	xcopy %LINUX_SRC%\Example*.?pp %MACOS_SRC% /DFY
	xcopy %LINUX_SRC%\Example*.?pp %WINDOWS_SRC% /DFY

	xcopy %MACOS_SRC%\Example*.?pp %CENTOS_SRC% /DFY
	xcopy %MACOS_SRC%\Example*.?pp %LINUX_SRC% /DFY
	xcopy %MACOS_SRC%\Example*.?pp %WINDOWS_SRC% /DFY

	xcopy %WINDOWS_SRC%\Example*.?pp %CENTOS_SRC% /DFY
	xcopy %WINDOWS_SRC%\Example*.?pp %LINUX_SRC% /DFY
	xcopy %WINDOWS_SRC%\Example*.?pp %MACOS_SRC% /DFY

endlocal

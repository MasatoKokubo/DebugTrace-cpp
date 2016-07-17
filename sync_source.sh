#! /bin/bash
LINUX_SRC=linux
MACOS_SRC=macos/src
WINDOWS_SRC=windows/src

cp -auv ${LINUX_SRC}/DebugTrace.?pp ${MACOS_SRC}
cp -auv ${LINUX_SRC}/DebugTrace.?pp ${WINDOWS_SRC}

cp -auv ${MACOS_SRC}/DebugTrace.?pp ${LINUX_SRC}
cp -auv ${MACOS_SRC}/DebugTrace.?pp ${WINDOWS_SRC}

cp -auv ${WINDOWS_SRC}/DebugTrace.?pp ${MACOS_SRC}
cp -auv ${WINDOWS_SRC}/DebugTrace.?pp ${LINUX_SRC}

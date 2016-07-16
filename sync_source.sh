#! /bin/bash
WINDOWS_SRC=windows/src
LINUX_SRC=linux

cp -auv ${WINDOWS_SRC}/DebugTrace.?pp ${LINUX_SRC}

cp -auv ${LINUX_SRC}/DebugTrace.?pp ${WINDOWS_SRC}

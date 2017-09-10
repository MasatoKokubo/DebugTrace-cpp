#! /bin/bash
LINUX_SRC=linux/src
MACOS_SRC=macos/src
WINDOWS_SRC=windows/src

cp -auv ${LINUX_SRC}/Example*.?pp ${MACOS_SRC}
cp -auv ${LINUX_SRC}/Example*.?pp ${WINDOWS_SRC}

cp -auv ${MACOS_SRC}/Example*.?pp ${LINUX_SRC}
cp -auv ${MACOS_SRC}/Example*.?pp ${WINDOWS_SRC}

cp -auv ${WINDOWS_SRC}/Example*.?pp ${MACOS_SRC}
cp -auv ${WINDOWS_SRC}/Example*.?pp ${LINUX_SRC}

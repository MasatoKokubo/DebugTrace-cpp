#! /bin/bash
cp -av DerivedData/DebugTrace/Build/Products/Debug/libDebugTrace.a /usr/local/lib
cp -av src/DebugTrace.hpp                                          /usr/local/include

chmod go+r /usr/local/lib/*
chmod go+r /usr/local/include/*

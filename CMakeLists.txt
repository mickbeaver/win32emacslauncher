cmake_minimum_required(VERSION 2.8)

# TODO Add support for building with MinGW. For now, this is what I did:
#   x86_64-w64-mingw32-windres.exe edit.rc edit.o
#   x86_64-w64-mingw32-g++.exe -c main.cpp
#   x86_64-w64-mingw32-g++.exe -municode -o edit.exe main.o edit.o
#   And copied libgcc_s_seh-1.dll, libstdc++-6.dll, and libwinpthread-1.dll

project(emacsclient_launcher)

set(RESOURCE_FILES edit.rc icon.ico resource.h)

add_executable(edit WIN32 main.cpp ${RESOURCE_FILES})
source_group(Resource\ Files FILES ${RESOURCE_FILES})


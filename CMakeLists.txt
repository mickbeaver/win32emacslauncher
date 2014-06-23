cmake_minimum_required(VERSION 2.8)

project(emacsclient_launcher)

set(RESOURCE_FILES edit.rc icon.ico resource.h)

add_executable(edit WIN32 main.cpp ${RESOURCE_FILES})
source_group(Resource\ Files FILES ${RESOURCE_FILES})



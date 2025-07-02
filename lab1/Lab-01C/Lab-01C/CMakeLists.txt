cmake_minimum_required(VERSION 3.16)
project(Lab-01C)

if(WIN32)
message(STATUS"Hello Windows!")
elseif(UNIX)
message(STATUS"Hello Linux!")
endif()

add_executable(Lab-01C Lab-01C.c)

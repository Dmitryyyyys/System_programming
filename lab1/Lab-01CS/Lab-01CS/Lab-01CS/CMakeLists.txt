cmake_minimum_required(VERSION 3.16)

project(Lab-01CS LANGUAGES CSharp)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
message("Hello, I am Windows!")
else(CMAKE_SYSTEM_NAME STREQUAL "Linux") 
message("Hello, I am Linux!")
endif()

add_executable(Lab-01CS Program.cs)

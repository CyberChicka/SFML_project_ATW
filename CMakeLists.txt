cmake_minimum_required(VERSION 3.20)
project(test_sfml)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc ")

set(SFML_STATIC_LIBRARIES TRUE)

add_executable(test_sfml main.cpp Map.h Map.h Map.h view.h mission.h)

set(SFML_DIR "E:\\programm\\SFML-2.5.1\\lib\\cmake\\SFML")

target_link_libraries(test_sfml sfml-graphics sfml-audio)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_nodules")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

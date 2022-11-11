cmake_minimum_required(VERSION 3.16)
project(speech)

set(CMAKE_CXX_STANDARD 11)

add_executable(speech main.cpp speechManager.cpp speechManager.h speaker.h)
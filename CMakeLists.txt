cmake_minimum_required(VERSION 3.28)
project(dogs)

set(CMAKE_CXX_STANDARD 17)

add_executable(dogs main.cpp
        LinkedList.cpp
        LinkedList.h
        HashTable.cpp
        HashTable.h
        DogNode.cpp
        DogNode.h)

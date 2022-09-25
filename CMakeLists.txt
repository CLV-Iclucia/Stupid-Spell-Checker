cmake_minimum_required(VERSION 3.23)
project(Checker)

set(CMAKE_CXX_STANDARD 14)

add_executable(Checker main.cpp Trie.h Trie.cpp WordNode.h MyUtils.h)

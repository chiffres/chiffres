cmake_minimum_required(VERSION 3.31.6)
project(chiffres)

set(CMAKE_CXX_STANDARD 26)

add_library(chiffres STATIC Chiffre.cpp Chiffre.h)
add_library(ether STATIC Ether.cpp Ether.h)

install(FILES Chiffre.h Ether.h DESTINATION include)
install(TARGETS chiffres ether DESTINATION lib)


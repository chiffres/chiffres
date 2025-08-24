cmake_minimum_required(VERSION 3.31.6)
project(chiffres)

set(CMAKE_CXX_STANDARD 26)

add_library(chiffres STATIC Chiffres.cpp Chiffres.h)
add_library(ether STATIC Ether.cpp Ether.h)

install(FILES Chiffres.h Ether.h DESTINATION include)
install(TARGETS chiffres ether DESTINATION lib)


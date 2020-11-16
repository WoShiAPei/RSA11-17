cmake_minimum_required(VERSION 3.17)
project(RSA-master)

set(CMAKE_CXX_STANDARD 14)

add_executable(RSA-master main.cpp BigInteger.cpp BigInteger.h RSA.cpp RSA.h)
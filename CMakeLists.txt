cmake_minimum_required(VERSION 3.17)
project(spectrometer C)

set(CMAKE_C_STANDARD 99)

add_executable(spectrometer main.c readcsv.c readcsv.h)
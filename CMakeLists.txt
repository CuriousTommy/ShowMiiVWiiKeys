cmake_minimum_required(VERSION 3.8.2)
project(SHOW_MII_VWII_KEYS)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY Binary)

add_library(OTP OTP.cpp OTP.h)
add_executable(ShowMiiVWiiKeys main.cpp)
target_link_libraries (ShowMiiVWiiKeys PUBLIC OTP)
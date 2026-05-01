cmake_minimum_required(VERSION 3.21)
project(Project_Power_Quality_Waveform_Analyser C)

set(CMAKE_C_STANDARD 99)

add_executable(Project_Power_Quality_Waveform_Analyser main.c IO.h Waveform.h IO.cpp Waveform.cpp Waveform.c IO.c)


cmake_minimum_required(VERSION 3.20)
project(Project_Power_Quality_Waveform_Analyser C)

set(CMAKE_C_STANDARD 99)

add_executable(Project_Power_Quality_Waveform_Analyser
        main.c
        IO.c
        Waveform.c
)

add_executable(unit_tests
        unit_tests.c
        Waveform.c
)

add_executable(integration_tests
        integration_tests.c
        IO.c
        Waveform.c
)
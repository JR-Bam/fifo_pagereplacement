cmake_minimum_required(VERSION 3.5.0)
project(page_replacement_fifo VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCES
    main.cpp
    PageReplacer.cpp 
    PageReplacementResult.cpp
)
add_executable(page_replacement_fifo ${SOURCES})


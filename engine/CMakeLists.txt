cmake_minimum_required(VERSION 3.16)

add_library(engine OBJECT
        Engine.cpp
)

target_include_directories(engine PUBLIC
        ${INCLUDE_ENGINE}
)

target_link_libraries(engine
        network core
)

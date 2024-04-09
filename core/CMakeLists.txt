cmake_minimum_required(VERSION 3.16)

find_package(Boost)
if (NOT DEFINED Boost_FOUND)
    message(FATAL_ERROR "Can't find boost")
endif ()

add_library(core STATIC
        event-handler/EventHandler.cpp
)

target_include_directories(core PUBLIC
        ${INCLUDE_CORE}
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(core
        ${Boost_LIBRARIES}
        network
)

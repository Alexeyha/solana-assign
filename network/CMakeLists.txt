cmake_minimum_required(VERSION 3.16)

find_package(CURL REQUIRED)
if (NOT DEFINED CURL_FOUND)
    message(FATAL_ERROR "Can't find curl")
endif ()

add_library(network STATIC
        request-manager/RequestManager.cpp
        curl-wrapper/CurlWrapper.cpp
)

target_include_directories(network PUBLIC
        ${INCLUDE_NETWORK}
        ${CURL_INCLUDE_DIRS}
)

target_link_libraries(network ${CURL_LIBRARIES})

cmake_minimum_required(VERSION 3.16)

project(solana-latency)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/deps/jsoncons/include
)

set(INCLUDE_NETWORK ${PROJECT_SOURCE_DIR}/network)
add_subdirectory(network)

set(INCLUDE_CORE ${PROJECT_SOURCE_DIR}/core)
add_subdirectory(core)

set(INCLUDE_ENGINE ${PROJECT_SOURCE_DIR}/engine)
add_subdirectory(engine)

include(config.cmake)
src_executable(latency-tracking src/standard-deviation-tracking.cpp)
src_executable(cli-app src/command-line-app.cpp)


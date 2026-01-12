cmake_minimum_required(VERSION 4.1.1)
project(NetTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_compile_definitions(_WIN32_WINNT=0x0A00)

# Fetch third-party dependencies
include(FetchContent)
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-30-2
)
FetchContent_MakeAvailable(asio)

add_subdirectory(shared)
add_subdirectory(server)
add_subdirectory(client)

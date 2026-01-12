cmake_minimum_required(VERSION 4.1.1)
project(NetTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Fetch third-party dependencies
include(FetchContent)
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-30-2
)
FetchContent_MakeAvailable(asio)

# Create targets before we add per-target definitions / links
add_subdirectory(shared)
add_subdirectory(server)
add_subdirectory(client)

if (WIN32)
    # Target at least Windows 7; you can raise this (e.g., 0x0A00 for Windows 10)
    target_compile_definitions(server PRIVATE _WIN32_WINNT=0x0601)
    target_compile_definitions(client PRIVATE _WIN32_WINNT=0x0601)

    # Do NOT add POSIX thread libs on Windows; CMake+MSVC/Clang-cl will handle runtime.
else()
    # POSIX threads needed for Asio on Linux/macOS
    find_package(Threads REQUIRED)
    target_link_libraries(server PRIVATE Threads::Threads)
    target_link_libraries(client PRIVATE Threads::Threads)
endif()

# Optional: Silence Asio’s standalone macro mismatch by defining ASIO_STANDALONE if not using Boost
target_compile_definitions(server PRIVATE ASIO_STANDALONE)
target_compile_definitions(client PRIVATE ASIO_STANDALONE)

file(GLOB_RECURSE SHARED_SRC CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_library(shared STATIC ${SHARED_SRC})

target_include_directories(shared
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

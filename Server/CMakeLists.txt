cmake_minimum_required(VERSION 3.10)
project(Server VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

# root directory header and source files
set(HEADERS
        util.h
        )
set(SOURCES
        main.cpp
        )

# subdirectories
add_subdirectory("util")

link_directories(/usr/local/ssl/lib/)
add_executable(Server ${SOURCES} ${HEADERS})

# OpenSSL headers
target_include_directories(Server PUBLIC /usr/local/ssl/include/)

# OpenSSL libraries
target_link_libraries(Server ssl)
target_link_libraries(Server crypto)

cmake_minimum_required(VERSION 3.10)
project(Server VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

include_directories("inc")

# root directory header and source files
add_executable(
        Server

        "src/main.cpp"

        "inc/util.h"
        "inc/util/Tree.h"
)

## OpenSSL headers
#target_include_directories(Server PUBLIC /usr/local/ssl/include/)
#
## OpenSSL libraries
#link_directories(/usr/local/ssl/lib/)
#target_link_libraries(Server ssl)
#target_link_libraries(Server crypto)

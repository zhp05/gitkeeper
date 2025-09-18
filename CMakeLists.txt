cmake_minimum_required(VERSION 3.20)
project(gitkeeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(gitkeeper gitkeeper.cc)

install(TARGETS gitkeeper
        RUNTIME DESTINATION bin
        )
cmake_minimum_required(VERSION 3.10)
project(SentinelAI)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(SentinelAI
    src/main.cpp
    src/environment.cpp
    src/agent.cpp
    src/optimizer.cpp
    src/ids.cpp
)

cmake_minimum_required(VERSION 3.17)
project(Giscord)

set(CMAKE_CXX_STANDARD 17)

set(
        SOURCE_FILES
        ./src/Giscord.cpp
        ./src/DRPC.cpp
        ./src/GmodProcInfo.cpp
        ./src/utils.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/discord-rpc/include/)
add_subdirectory(discord-rpc)

link_directories(${PROJECT_SOURCE_DIR}/discord-rpc/src/Release)
link_libraries(discord-rpc)

add_executable(giscord ${SOURCE_FILES})
target_link_libraries(giscord discord-rpc)
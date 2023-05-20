cmake_minimum_required(VERSION 3.24)
project(projekt)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Ball.cpp Ball.h Paddle.cpp Paddle.h Block.cpp Block.h Controls.cpp Controls.h Arkanoid.cpp Arkanoid.h Menu.cpp Menu.h)
add_executable(projekt ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(projekt ${SFML_LIBRARIES})
endif()
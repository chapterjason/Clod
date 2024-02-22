cmake_minimum_required(VERSION 3.28)
project(Clod VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY git@github.com:SFML/SFML.git
        GIT_TAG 2.6.x)

FetchContent_Declare(Box2D
        GIT_REPOSITORY git@github.com:erincatto/box2d.git
        GIT_TAG v2.4.1)

set(BUILD_SHARED_LIBS false)
FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(Box2D)

add_library(${PROJECT_NAME} STATIC
        include/Clod/Geometry/Position.hpp
        include/Clod/Geometry/Bridge.hpp
        src/Clod/Geometry/Position.cpp
        src/Clod/Geometry/Bridge.cpp
        include/Clod/Geometry.hpp
        include/Clod/System/Time.hpp
        src/Clod/System/Time.cpp
        include/Clod/System.hpp
        include/Clod/System/Type.hpp
        include/Clod/System/Type.inl
)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio sfml-system sfml-window sfml-network box2d)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST}
)

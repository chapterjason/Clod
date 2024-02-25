cmake_minimum_required(VERSION 3.28)
project(Clod VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY git@github.com:SFML/SFML.git
        GIT_TAG master)

FetchContent_Declare(Box2D
        GIT_REPOSITORY git@github.com:erincatto/box2d.git
        GIT_TAG v2.4.1)

FetchContent_Declare(CDT
        GIT_REPOSITORY git@github.com:artem-ogre/CDT.git
        GIT_TAG master)

FetchContent_MakeAvailable(CDT)
set(CDT_USE_AS_COMPILED_LIBRARY true)
add_subdirectory(${cdt_SOURCE_DIR}/CDT ${cdt_BINARY_DIR})

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
        include/Clod/Core/ResourceManager.hpp
        include/Clod/Core/ImageResourceManager.hpp
        src/Clod/Core/ImageResourceManager.cpp
        include/Clod/Core/TextureResourceManager.hpp
        src/Clod/Core/TextureResourceManager.cpp
        include/Clod/Core/FontResourceManager.hpp
        src/Clod/Core/FontResourceManager.cpp
        include/Clod/Graphic.hpp
        include/Clod/Core/MusicResourceManager.hpp
        src/Clod/Core/MusicResourceManager.cpp
        include/Clod/Core/SoundBufferResourceManager.hpp
        src/Clod/Core/SoundBufferResourceManager.cpp
        include/Clod/Core/SoundResourceManager.hpp
        src/Clod/Core/SoundResourceManager.cpp
        include/Clod/Graphic/Image.hpp
        src/Clod/Graphic/Image.cpp
        include/Clod/Core.hpp
        include/Clod/Algorithm/RamerDouglasPeucker.hpp
        src/Clod/Algorithm/RamerDouglasPeucker.cpp
        include/Clod/Algorithm.hpp
        include/Clod/Algorithm/JarvisMarch.hpp
        src/Clod/Algorithm/JarvisMarch.cpp
        include/Clod/Geometry/Hull.hpp
        src/Clod/Geometry/Hull.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio sfml-system sfml-window sfml-network box2d CDT)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST}
)

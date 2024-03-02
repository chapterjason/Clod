cmake_minimum_required(VERSION 3.28)
project(Clod VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

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
        include/Clod/Geometry/Bridge.hpp
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
        include/Clod/Core/SpriteResourceManager.hpp
        src/Clod/Core/FontResourceManager.cpp
        src/Clod/Core/SpriteResourceManager.cpp
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
        include/Clod/Algorithm.hpp
        include/Clod/Algorithm/JarvisMarch.hpp
        src/Clod/Algorithm/JarvisMarch.cpp
        include/Clod/Geometry/ConcaveHull.hpp
        src/Clod/Geometry/ConcaveHull.cpp
        include/Clod/Geometry/Edge.hpp
        src/Clod/Geometry/Edge.cpp
        include/Clod/Geometry/Polygon.hpp
        src/Clod/Geometry/Polygon.cpp
        include/Clod/Geometry/Polycomplex.hpp
        src/Clod/Geometry/Polycomplex.cpp
        include/Clod/Geometry/Vertex.hpp
        src/Clod/Geometry/Vertex.cpp
        include/Clod/Geometry/Chain.hpp
        src/Clod/Geometry/Chain.cpp
        include/Clod/Geometry/Cluster.hpp
        src/Clod/Geometry/Cluster.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio sfml-system sfml-window sfml-network box2d CDT)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST}
)

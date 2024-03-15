cmake_minimum_required(VERSION 3.28)
project(Clod VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Add CPM module
set(CPM_DOWNLOAD_VERSION 0.38.7)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

# Dependencies
CPMAddPackage(
        NAME Ccache.cmake
        GIT_REPOSITORY git@github.com:TheLartians/Ccache.cmake.git
        GIT_TAG master
)

CPMAddPackage(
        NAME SFML
        GIT_REPOSITORY "git@github.com:SFML/SFML.git"
        GIT_TAG "master"
        OPTIONS
            "SFML_BUILD_EXAMPLES false"
            "SFML_BUILD_DOC false"
            "BUILD_SHARED_LIBS false"
)

CPMAddPackage(
        NAME Box2D
        GIT_REPOSITORY "git@github.com:erincatto/box2d.git"
        GIT_TAG "main"
        OPTIONS
            "BUILD_SHARED_LIBS false"
            "BOX2D_BUILD_TESTBED false"
            "BOX2D_BUILD_UNIT_TESTS false"
        # BOX2D_USER_SETTINGS true #
)

CPMAddPackage(
        NAME CDT
        GIT_REPOSITORY "git@github.com:artem-ogre/CDT.git"
        GIT_TAG "master"
        SOURCE_SUBDIR CDT
        OPTIONS
            "CDT_USE_AS_COMPILED_LIBRARY true"
)

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
        include/Clod/Resource/PathType.hpp
        include/Clod/Resource/Path.hpp
        src/Clod/Resource/Path.cpp
        include/Clod/Resource.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio sfml-system sfml-window sfml-network box2d CDT)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST}
)

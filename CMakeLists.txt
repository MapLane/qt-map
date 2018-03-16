cmake_minimum_required(VERSION 3.9)
project(qt_map)
set(OPENSSL_ROOT_DIR /usr/local/opt/openssl/include)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(OPENSSL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Qt5Core       REQUIRED)
find_package(Qt5WebSockets REQUIRED)
#find_package(Qt5Gui      REQUIRED)
#find_package(Qt5Network  REQUIRED)
#find_package(Qt5OpenGL   REQUIRED)
find_package(Qt5Widgets  REQUIRED)
#find_package(Qt5Sql      REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(MBLIB ${PROJECT_SOURCE_DIR}/lib/libqmapboxgl)

add_library(${PROJECT_NAME} SHARED
        src/mapwindow.cpp
        src/mapwindow.hpp
        src/locationsocket.cpp
        src/locationsocket.hpp)

include_directories(
        ${MBLIB}/include
        ${PROJECT_NAME}/include
        ${OPENSSL_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME}
        ${ZLIB_LIBRARIES}
        ${MBLIB}/lib/libqmapboxgl.dylib
        Qt5::Widgets
        Qt5::WebSockets
        libuv.dylib
        libuWS.dylib
        libssl.dylib
        )

add_executable(map src/main.cpp)

target_link_libraries(map
        ${PROJECT_NAME})


cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set (CMAKE_CXX_STANDARD 11)
project( gng )

set(INCLUDE_DIR include)
set(HEADER_FILES
    ${INCLUDE_DIR}/Graph/Graph.h
    ${INCLUDE_DIR}/Graph/Graph.tpp
    ${INCLUDE_DIR}/Graph/Node.h
    ${INCLUDE_DIR}/Graph/Node.tpp
    ${INCLUDE_DIR}/Graph/Edge.h
    ${INCLUDE_DIR}/GNG.h
    ${INCLUDE_DIR}/Image.h
    )

set(SRC_DIR src)
set(SOURCES
    main.cpp
    ${SRC_DIR}/GNG.cpp
    ${SRC_DIR}/Image.cpp
    )

find_package( OpenCV REQUIRED )
add_executable(gng ${SOURCES} ${HEADER_FILES})

target_link_libraries( gng ${OpenCV_LIBS} )
target_include_directories(gng PRIVATE ${INCLUDE_DIR})
cmake_minimum_required(VERSION 2.8)

project(FileServer)

add_compile_options(-std=c++11)

find_package(Boost 1.58.0 REQUIRED system thread)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    set(LIBS ${Boost_LIBRARIES})
endif()

include_directories(headers)
set(HEADER_FILES server/server.h server/connection.h server/serverhandler.h http/request.h http/parser.h http/header.h http/mime.h)
set(SOURCE_FILES main.cpp server/server.cpp server/connection.cpp server/serverhandler.cpp http/response.cpp http/parser.cpp http/mime.cpp)
add_executable(FileServer ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(FileServer -lpthread ${LIBS})

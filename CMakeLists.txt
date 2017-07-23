cmake_minimum_required(VERSION 2.8)

project(FileServer)

add_compile_options(-std=c++11)

find_package(Boost 1.58.0 REQUIRED system thread)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    set(LIBS ${Boost_LIBRARIES})
endif()

add_executable(${PROJECT_NAME} "main.cpp" "server/server.cpp" "server/connection.cpp" "server/serverhandler.cpp" "http/request.cpp" "http/response.cpp" "http/parser.cpp")

target_link_libraries(FileServer -lpthread ${LIBS})

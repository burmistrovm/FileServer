cmake_minimum_required(VERSION 2.8)

project(FileServer)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.58.0 REQUIRED system thread)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    set(LIBS ${Boost_LIBRARIES})
endif()

add_executable(${PROJECT_NAME} "main.cpp" "server/server.cpp" "http/request.cpp" "http/response.cpp")

target_link_libraries(FileServer -lpthread ${LIBS})

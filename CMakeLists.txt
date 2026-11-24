cmake_minimum_required(VERSION 3.22)

project(tosiek VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable(${PROJECT_NAME} ${SRC})

find_package(dpp CONFIG REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(OPUS REQUIRED opus)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    dpp::dpp
    pthread
    ${OPUS_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${OPUS_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

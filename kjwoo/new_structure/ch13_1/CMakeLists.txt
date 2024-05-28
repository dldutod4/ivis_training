cmake_minimum_required(VERSION 3.11)

project(testCode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC
"${CMAKE_SOURCE_DIR}/src/*.cpp"
)

message(${SRC})

add_executable(${CMAKE_PROJECT_NAME} ${SRC})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
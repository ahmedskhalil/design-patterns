cmake_minimum_required(VERSION 3.0.0)
project(design-patterns VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include(CTest)
# enable_testing()

add_executable(observer-pattern src/observer-pattern.cpp)
add_executable(visitor-pattern src/visitor-pattern.cpp)
add_executable(builder-pattern src/builder-pattern.cpp)
add_executable(factory-method-pattern src/factory-method-pattern.cpp)
add_executable(adapter-pattern src/adapter-pattern.cpp)
add_executable(bridge-pattern src/bridge-pattern.cpp)
add_executable(abstract-factory-pattern src/abstract-factory-pattern.cpp)
add_executable(prototype-pattern src/prototype-pattern.cpp)


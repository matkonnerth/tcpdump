project(opcua CXX)

add_library(opcua SHARED opcua_api.cpp)
target_include_directories(opcua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
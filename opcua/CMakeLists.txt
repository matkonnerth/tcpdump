project(opcua CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(opcua opcua_api.cpp Server.cpp)
target_include_directories(opcua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(opcua PUBLIC open62541.a)
target_link_libraries(opcua PRIVATE stdc++)
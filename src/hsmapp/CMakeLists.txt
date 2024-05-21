include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(hsmapp
    #main.cpp
    #type_erasure_poc.cpp
    visitor.cpp)

target_link_libraries(hsmapp PUBLIC
    hsmlib
)

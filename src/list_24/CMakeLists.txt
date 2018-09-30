file(GLOB SRC ${algorithms_SOURCE_DIR}/src/list_24/*.cpp)

add_executable(list_24 ${SRC})

target_link_libraries(
    list_24
    ${Boost_LIBRARIES}
)

file(GLOB SRC ${algorithms_SOURCE_DIR}/src/table-converter/*.cpp)

add_executable(table-converter ${SRC})

target_link_libraries(
    table-converter
    ${Boost_LIBRARIES}
)

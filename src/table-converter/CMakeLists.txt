file(GLOB SRC ${algorithms_SOURCE_DIR}/src/table-converter/*.cpp)
file(GLOB H_SRC ${algorithms_SOURCE_DIR}/src/table-converter/*.h)

add_executable(table-converter ${SRC} ${H_SRC})

target_link_libraries(
    table-converter
    ${Boost_LIBRARIES}
)

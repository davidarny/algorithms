file(GLOB SRC ${algorithms_SOURCE_DIR}/src/expression-tree/*.cpp)
file(GLOB H_SRC ${algorithms_SOURCE_DIR}/src/expression-tree/*.h)

add_executable(expression-tree ${SRC} ${H_SRC})

target_link_libraries(
    expression-tree
    ${Boost_LIBRARIES}
)

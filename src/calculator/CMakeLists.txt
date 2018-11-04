file(GLOB SRC ${algorithms_SOURCE_DIR}/src/calculator/*.cpp)
file(GLOB H_SRC ${algorithms_SOURCE_DIR}/src/expression-tree/*.h)

add_executable(calculator ${SRC} ${H_SRC})

target_link_libraries(
    calculator
    ${Boost_LIBRARIES}
)

file(GLOB SRC ${algorithms_SOURCE_DIR}/src/calculator/*.cpp)

add_executable(calculator ${SRC})

target_link_libraries(
    calculator
    ${Boost_LIBRARIES}
)

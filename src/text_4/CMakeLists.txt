file(GLOB SRC ${algorithms_SOURCE_DIR}/src/text_4/*.cpp)

add_executable(text_4 ${SRC})

target_link_libraries(
    text_4
    ${Boost_LIBRARIES}
)

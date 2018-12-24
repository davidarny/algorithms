file(GLOB SRC ${algorithms_SOURCE_DIR}/src/phonebook/*.cpp)
file(GLOB H_SRC ${algorithms_SOURCE_DIR}/src/phonebook/*.h)

add_executable(phonebook ${SRC} ${H_SRC})

target_link_libraries(
    phonebook
    ${Boost_LIBRARIES}
)

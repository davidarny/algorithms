file(GLOB SRC ${algorithms_SOURCE_DIR}/src/**/*.cpp)
file(GLOB TEST_SRC ${algorithms_SOURCE_DIR}/test/**/*.cpp)

list(FILTER SRC EXCLUDE REGEX ".*main.cpp$")

include_directories(${algorithms_SOURCE_DIR}/src ${algorithms_SOURCE_DIR}/lib/doctest)

add_executable(Test test.cpp ${SRC} ${TEST_SRC})

target_link_libraries(
    Test
    ${Boost_LIBRARIES}
)

file(GLOB SRC ${algorithms_SOURCE_DIR}/src/list_24/*.cpp)
file(GLOB UTILS_SRC ${algorithms_SOURCE_DIR}/test/utils/*.cpp)

list(FILTER SRC EXCLUDE REGEX ".*main.cpp$")

include_directories(${algorithms_SOURCE_DIR}/src ${algorithms_SOURCE_DIR}/lib/doctest)

add_executable(test_list_24 main.cpp list_24.cpp ${SRC} ${UTILS_SRC})

target_link_libraries(
    test_list_24
    ${Boost_LIBRARIES}
)

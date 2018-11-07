file(GLOB SRC ${algorithms_SOURCE_DIR}/src/expression-tree/*.cpp)
file(GLOB H_SRC ${algorithms_SOURCE_DIR}/src/expression-tree/*.h)
file(GLOB UTILS_SRC ${algorithms_SOURCE_DIR}/test/utils/*.cpp)
file(GLOB H_UTILS_SRC ${algorithms_SOURCE_DIR}/test/utils/*.h)

list(FILTER SRC EXCLUDE REGEX ".*main.cpp$")

include_directories(${algorithms_SOURCE_DIR}/src ${algorithms_SOURCE_DIR}/lib/doctest)

add_executable(expression-tree_test main.cpp expression-tree.spec.cpp ${SRC} ${H_SRC} ${UTILS_SRC} ${H_UTILS_SRC})

target_link_libraries(
    expression-tree_test
    ${Boost_LIBRARIES}
)

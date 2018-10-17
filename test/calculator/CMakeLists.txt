file(GLOB SRC ${algorithms_SOURCE_DIR}/src/calculator/*.cpp)
file(GLOB UTILS_SRC ${algorithms_SOURCE_DIR}/test/utils/*.cpp)

list(FILTER SRC EXCLUDE REGEX ".*main.cpp$")

include_directories(${algorithms_SOURCE_DIR}/src ${algorithms_SOURCE_DIR}/lib/doctest)

add_executable(calculator_test main.cpp calculator.spec.cpp ${SRC} ${UTILS_SRC})

target_link_libraries(
    calculator_test
    ${Boost_LIBRARIES}
)

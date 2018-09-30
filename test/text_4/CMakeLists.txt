file(GLOB SRC ${algorithms_SOURCE_DIR}/src/text_4/*.cpp)
file(GLOB UTILS_SRC ${algorithms_SOURCE_DIR}/test/utils/*.cpp)

list(FILTER SRC EXCLUDE REGEX ".*main.cpp$")

include_directories(${algorithms_SOURCE_DIR}/src ${algorithms_SOURCE_DIR}/lib/doctest)

add_executable(test_text_4.cpp main.cpp text_4.cpp ${SRC} ${UTILS_SRC})

target_link_libraries(
    test_text_4.cpp
    ${Boost_LIBRARIES}
)

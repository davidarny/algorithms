file(GLOB SRC ${algorithms_SOURCE_DIR}/src/aeroflot/*.cpp)
file(GLOB H_SRC ${algorithms_SOURCE_DIR}/src/aeroflot/*.h)
file(GLOB UTILS_SRC ${algorithms_SOURCE_DIR}/test/utils/*.cpp)
file(GLOB H_UTILS_SRC ${algorithms_SOURCE_DIR}/test/utils/*.h)

list(FILTER SRC EXCLUDE REGEX ".*main.cpp$")

include_directories(${algorithms_SOURCE_DIR}/src ${algorithms_SOURCE_DIR}/lib/doctest)

add_executable(aeroflot_test main.cpp aeroflot.spec.cpp ${SRC} ${H_SRC} ${UTILS_SRC} ${H_UTILS_SRC})

target_link_libraries(
    aeroflot_test
    ${Boost_LIBRARIES}
)

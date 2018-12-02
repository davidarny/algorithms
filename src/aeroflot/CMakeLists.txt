file(GLOB SRC ${algorithms_SOURCE_DIR}/src/aeroflot/*.cpp)
file(GLOB H_SRC ${algorithms_SOURCE_DIR}/src/aeroflot/*.h)

add_executable(aeroflot ${SRC} ${H_SRC})

target_link_libraries(
    aeroflot
    ${Boost_LIBRARIES}
)

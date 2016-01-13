set(CLIENT daytime_client)
add_executable(${CLIENT} client.cpp)
target_link_libraries (${CLIENT} ${Boost_LIBRARIES})
install (TARGETS ${CLIENT} RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)

set(SERVER daytime_server)
add_executable(${SERVER} server.cpp)
target_link_libraries (${SERVER} ${Boost_LIBRARIES})
install (TARGETS ${SERVER} RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)

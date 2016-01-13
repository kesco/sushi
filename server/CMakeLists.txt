set(SERVER server)
add_executable(${SERVER} server.cpp)
target_link_libraries (${SERVER} ${Boost_LIBRARIES})
install (TARGETS ${SERVER} RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)

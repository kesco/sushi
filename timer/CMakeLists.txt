add_executable(timer timer.cpp)
target_link_libraries (timer ${Boost_LIBRARIES})
install (TARGETS timer RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)

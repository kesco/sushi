file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(TEST_FILE ${SOURCES})
  get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
  add_executable(${TEST_NAME} ${TEST_FILE})
  set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
  target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES})
  add_test(NAME ${TEST_NAME} 
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/bin
    COMMAND ${PROJECT_BINARY_DIR}/bin/${TEST_NAME} )
endforeach(TEST_FILE)


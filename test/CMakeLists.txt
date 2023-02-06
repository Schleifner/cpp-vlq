find_package(GTest REQUIRED)
file(GLOB test_sources CONFIGURE_DEPENDS ./*.cpp)
add_executable(
  vlq_test
  ${test_sources}
)
file(GLOB sources ../src/*.cpp ../src/*.hpp)
target_sources(vlq_test PUBLIC ${sources})
target_link_libraries(
  vlq_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(vlq_test)

if(CMAKE_COMPILER_IS_GNUCXX)
    LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    setup_target_for_coverage_gcovr_xml(NAME cov
                              EXECUTABLE vlq_test
                              DEPENDENCIES vlq_test
                              BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/src")

    setup_target_for_coverage_gcovr_html(NAME cov_html 
                              EXECUTABLE vlq_test
                              DEPENDENCIES vlq_test
                              BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/src")                              
endif()

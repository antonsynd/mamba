file(GLOB_RECURSE TEST_SOURCES *.cpp)

enable_testing()

add_executable(mamba-unit-tests ${TEST_SOURCES})

target_link_libraries(mamba-unit-tests
  mamba
  GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(mamba-unit-tests)

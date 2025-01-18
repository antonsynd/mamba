file(GLOB_RECURSE CPP_FILES *.cpp)

# Initialize separate lists for test and non-test files
set(TEST_SOURCES "")
set(TEST_LIB_SOURCES "")

# Loop through all collected files and categorize them
foreach(FILE IN LISTS CPP_FILES)
    if(FILE MATCHES "/test_.*\\.cpp$")
        list(APPEND TEST_SOURCES ${FILE})
    else()
        list(APPEND TEST_LIB_SOURCES ${FILE})
    endif()
endforeach()

add_library(mamba-test ${TEST_LIB_SOURCES})

enable_testing()

add_executable(mamba-unit-tests ${TEST_SOURCES})

target_link_libraries(mamba-unit-tests
  mamba
  mamba-test
  GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(mamba-unit-tests)

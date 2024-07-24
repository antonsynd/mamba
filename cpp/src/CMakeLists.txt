# Add the source files for the library
file(GLOB_RECURSE LIBRARY_SOURCES src/*.cpp)

# Add the library target
add_library(libMamba ${LIBRARY_SOURCES})

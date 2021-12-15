cmake_minimum_required(VERSION 3.0.0)
project(rocksjni-m2 VERSION 0.1.0)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
# Require (at least) it
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

add_executable(rocksjni-m2 main.cpp)
include_directories(lib) # our code
target_sources(rocksjni-m2 PRIVATE lib/jniapi.cpp lib/mirrorapi.cpp lib/rocksapi.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(rocksjni-m2 PRIVATE gtest gtest_main) # link google test to this executable
include(GoogleTest)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

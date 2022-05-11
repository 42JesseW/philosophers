cmake_minimum_required(VERSION 3.17)
project(tests LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES unittests/*.cpp)
file(GLOB_RECURSE MAIN_SOURCES ../philo/srcs/*.c)
list(FILTER MAIN_SOURCES EXCLUDE REGEX ../srcs/main.c)

enable_testing()

add_executable(tests ${TEST_SOURCES} ${MAIN_SOURCES})
target_include_directories(tests PUBLIC unittests PUBLIC ../philo/includes)
target_link_libraries(tests gtest_main pthread)

add_definitions(-DTESTRUN)

include(GoogleTest)
gtest_discover_tests(tests)

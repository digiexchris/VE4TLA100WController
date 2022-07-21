cmake_minimum_required(VERSION 3.16)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

add_executable(tests 020-TestCase-1.cpp 020-TestCase-2.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2)

project(Tests)
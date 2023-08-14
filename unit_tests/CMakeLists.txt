cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME unit_tests)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME}
        main.cpp
        InvertedIndex_test/InvertedIndexBasicTest.cpp
        WordHandler_test/WordHandlerBasicTest.cpp
        SearchServer_test/SearchServerBasicTest.cpp
        ../src/InvertedIndex.cpp ../include/InvertedIndex.h
        ../src/WordHandler.cpp ../include/WordHandler.h
        ../src/SearchServer.cpp ../include/SearchServer.h
        )

target_include_directories(${PROJECT_NAME} PUBLIC ../include)

target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
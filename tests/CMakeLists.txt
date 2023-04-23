include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1_test lab1_test.cpp ../lab1/src/radix_sort.cpp ../lab1/include/radix_sort.h)
target_link_libraries(lab1_test PRIVATE GTest::GTest)
target_include_directories(lab1_test PRIVATE ../lab1/include)
add_test(lab1_test lab1_test)


add_executable(radix_sort_test radix_sort_test.cpp ../radix_sort/src/sort.cpp ../radix_sort/include/sort.h)
target_link_libraries(radix_sort_test PRIVATE GTest::GTest)
target_include_directories(radix_sort_test PRIVATE ../radix_sort/include)
add_test(radix_sort_test radix_sort_test)


add_executable(treap_test treap_test.cpp ../treap/include/treap.h ../treap/src/treap.cpp)
target_link_libraries(treap_test PRIVATE GTest::GTest)
target_include_directories(treap_test PRIVATE ../treap/include)
add_test(treap_test treap_test)


add_executable(avl_test avl_test.cpp ../avl/include/avl.hpp)
target_link_libraries(avl_test PRIVATE GTest::GTest)
target_include_directories(avl_test PRIVATE ../avl/include)
add_test(avl_test avl_test)
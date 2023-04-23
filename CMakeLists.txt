cmake_minimum_required(VERSION 3.20)

project(DA_LABS C CXX)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(lab1)
add_subdirectory(lab2_treap)
add_subdirectory(lab2_avl)

add_subdirectory(radix_sort)
add_subdirectory(treap)
add_subdirectory(avl)

add_subdirectory(tests)

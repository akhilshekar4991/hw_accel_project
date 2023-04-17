cmake_minimum_required(VERSION 3.0.0)
project(hello_cmake VERSION 0.1.0)

add_compile_options(-Ofast)

add_executable(test.out load_factor_study/03_construct_probe_hash_map.cpp)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(json)
add_subdirectory(hopscotch-map)

target_link_libraries(test.out PRIVATE tsl::hopscotch_map nlohmann_json) 

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)

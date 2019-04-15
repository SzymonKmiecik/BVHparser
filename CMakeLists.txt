cmake_minimum_required (VERSION 3.10)

project (BVHparser)


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-local-typedef -Werror -std=c++14")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")



SET_SOURCE_FILES_PROPERTIES(${source_dir}/tinyfiledialogs.c PROPERTIES LANGUAGE CXX )
file (GLOB_RECURSE source_files "${source_dir}/*.cpp")
file (GLOB_RECURSE header_files "${source_dir}/*.h")

add_executable (BVHparser ${source_files} ${header_files} ${source_dir}/tinyfiledialogs.c)

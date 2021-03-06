cmake_minimum_required (VERSION 3.6.0 FATAL_ERROR)

if (PEGTL_PLATFORM STREQUAL "Android")
  # This must be before project()
  set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/android.toolchain.cmake")
  set(ANDROID_ABI "x86" CACHE STRING "")
  set(ANDROID_TOOLCHAIN "clang" CACHE STRING "")
  set(ANDROID_NATIVE_API_LEVEL "android-16" CACHE STRING "")
endif()

project (PEGTL)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8 /W4 /WX")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set (CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
  set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g -DNDEBUG")
  set (CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set (CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
  set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g -DNDEBUG")
  set (CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")
else ()
  message (FATAL_ERROR "Unknown C++ compiler: ${CMAKE_CXX_COMPILER_ID}" )
endif ()

enable_testing ()

include_directories (${CMAKE_SOURCE_DIR})

file (GLOB testsources unit_tests/*.cc)
foreach (testsourcefile ${testsources})
  get_filename_component (exename ${testsourcefile} NAME_WE)
  add_executable (${exename} ${testsourcefile})
  if (PEGTL_PLATFORM STREQUAL "Android")
    add_test (NAME ${exename} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/run-on-android.sh ${CMAKE_BINARY_DIR}/${exename})
  else ()
    add_test (NAME ${exename} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${CMAKE_BINARY_DIR}/${exename})
  endif ()
endforeach (testsourcefile)

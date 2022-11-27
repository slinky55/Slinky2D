# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/shaft/Slinky2D/build/_deps/googletest-src"
  "/Users/shaft/Slinky2D/build/_deps/googletest-build"
  "/Users/shaft/Slinky2D/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "/Users/shaft/Slinky2D/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/Users/shaft/Slinky2D/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/Users/shaft/Slinky2D/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/Users/shaft/Slinky2D/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/shaft/Slinky2D/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/shaft/Slinky2D/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/1School/OOPL/OOPL_PTSD_pushBox/PTSD/lib/spdlog"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/spdlog-build"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix/tmp"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

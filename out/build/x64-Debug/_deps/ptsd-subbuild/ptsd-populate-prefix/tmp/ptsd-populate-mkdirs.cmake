# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/PTSD"
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/ptsd-build"
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/ptsd-subbuild/ptsd-populate-prefix"
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/ptsd-subbuild/ptsd-populate-prefix/tmp"
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/ptsd-subbuild/ptsd-populate-prefix/src/ptsd-populate-stamp"
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/ptsd-subbuild/ptsd-populate-prefix/src"
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/ptsd-subbuild/ptsd-populate-prefix/src/ptsd-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/ptsd-subbuild/ptsd-populate-prefix/src/ptsd-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/ptsd-subbuild/ptsd-populate-prefix/src/ptsd-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

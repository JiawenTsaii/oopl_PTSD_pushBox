# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/PTSD/lib/sdl2"
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2-build"
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2-subbuild/sdl2-populate-prefix"
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2-subbuild/sdl2-populate-prefix/tmp"
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2-subbuild/sdl2-populate-prefix/src/sdl2-populate-stamp"
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2-subbuild/sdl2-populate-prefix/src"
  "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2-subbuild/sdl2-populate-prefix/src/sdl2-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2-subbuild/sdl2-populate-prefix/src/sdl2-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2-subbuild/sdl2-populate-prefix/src/sdl2-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

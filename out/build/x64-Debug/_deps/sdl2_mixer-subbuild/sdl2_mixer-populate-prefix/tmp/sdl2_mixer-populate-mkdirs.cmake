# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/1School/OOPL/OOPL_PTSD_pushBox/PTSD/lib/sdl2_mixer"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2_mixer-build"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/tmp"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/sdl2_mixer-subbuild/sdl2_mixer-populate-prefix/src/sdl2_mixer-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

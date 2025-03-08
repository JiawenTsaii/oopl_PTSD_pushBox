# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/1School/OOPL/OOPL_PTSD_pushBox/PTSD/lib/nlohmann_json"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/nlohmann_json-build"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/nlohmann_json-subbuild/nlohmann_json-populate-prefix"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/nlohmann_json-subbuild/nlohmann_json-populate-prefix/tmp"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/nlohmann_json-subbuild/nlohmann_json-populate-prefix/src/nlohmann_json-populate-stamp"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/nlohmann_json-subbuild/nlohmann_json-populate-prefix/src"
  "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/nlohmann_json-subbuild/nlohmann_json-populate-prefix/src/nlohmann_json-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/nlohmann_json-subbuild/nlohmann_json-populate-prefix/src/nlohmann_json-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/1School/OOPL/OOPL_PTSD_pushBox/out/build/x64-Debug/_deps/nlohmann_json-subbuild/nlohmann_json-populate-prefix/src/nlohmann_json-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

if (NOT EXISTS "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/install_manifest.txt\"")
endif(NOT EXISTS "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/install_manifest.txt")

file(READ "E:/1School/OOPL/z_trytry/oopl_PTSD_pushBox/out/build/x64-Debug/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach(file)


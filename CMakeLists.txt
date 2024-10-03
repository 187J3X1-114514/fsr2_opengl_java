cmake_minimum_required(VERSION 3.15)
project (fsr2_java_lib)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g")
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DON_LINUX)
    add_definitions(-DFFX_GCC)

endif()
MESSAGE( STATUS "${CMAKE_SYSTEM_NAME}")


if (CMAKE_SYSTEM_NAME MATCHES "Linux")
find_library(LIB_FSR2_GL ffx_fsr2_api_gl_x64 ${PROJECT_BINARY_DIR}/../bin)
find_library(LIB_FSR2_API ffx_fsr2_api_x64 ${PROJECT_BINARY_DIR}/../bin)
set(FFX_SC_EXECUTABLE
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/FidelityFX_SC.sh)
else()
find_library(LIB_FSR2_GL libffx_fsr2_api_gl_x64 ${PROJECT_BINARY_DIR}/../bin)
find_library(LIB_FSR2_API libffx_fsr2_api_x64 ${PROJECT_BINARY_DIR}/../bin)
set(FFX_SC_EXECUTABLE
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/FidelityFX_SC.exe)
endif()


include_directories(${PROJECT_BINARY_DIR}/../include ${PROJECT_BINARY_DIR}/../src)

add_library(ffx_lib_glad INTERFACE)
target_include_directories(ffx_lib_glad INTERFACE ${PROJECT_BINARY_DIR}/../include)
add_subdirectory(src/ffx-fsr2-api)
find_package(OpenGL REQUIRED)

aux_source_directory(${PROJECT_BINARY_DIR}/../src ALL_SRC)

add_library(lib_shared SHARED ${ALL_SRC})
add_dependencies(lib_shared ffx_fsr2_api_gl_x64 ffx_fsr2_api_x64)
set_target_properties(lib_shared PROPERTIES OUTPUT_NAME "fsr2javalib")

if(IGLIBFSR2API)
    target_link_libraries(lib_shared ${LIB_FSR2_GL} ${LIB_FSR2_API})
endif()

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

#mingw32-make
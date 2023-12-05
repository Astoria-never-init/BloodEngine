cmake_minimum_required(VERSION 3.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_compile_options(-std=c++11)

set(LIBRARY_DIR ${CMAKE_SOURCE_DIR}/libs)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(GLAD ${LIBRARY_DIR}/src/glad.c )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})
#defines

if(WIN32)
    set(wxWidgets_ROOT_DIR "D:/SF_Blood_engine/BloodEngine/libs/WxWidgets")
    set(wxWidgets_LIB_DIR "D:/SF_Blood_engine/BloodEngine/libs/WxWidgets/lib/vc14x_x64_dll")

    set(platform_liblink_list
        tinyxml2.lib
    )
elseif(UNIX)
    set(wxWidgets_ROOT_DIR "/usr/local/lib/wx")

    set(platform_liblink_list
        libtinyxml2.a
    )
endif()

file(GLOB INCLUDES "${LIBRARY_DIR}/include/*")
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")

#end



project(test)



find_package(Threads REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS core base xml xrc html gl)
include(${wxWidgets_USE_FILE})


include_directories(${INCLUDES} ${SRC_DIR} ${wxWidgets_INCLUDE_DIRS})
link_directories(${LIBRARY_DIR}/lib/xml)
		

add_executable(testbuild ${SOURCES} ${GLAD})


target_link_libraries(testbuild PRIVATE ${platform_liblink_list} ${wxWidgets_LIBRARIES})
target_compile_definitions(testbuild PRIVATE ${wxWidgets_DEFINITIONS})


cmake_minimum_required(VERSION 3.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_compile_options(-std=c++11)


set(LIBRARY_DIR ${CMAKE_SOURCE_DIR}/libs)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(GLAD ${LIBRARY_DIR}/init/src/glad.c )



project(test)



find_package(Threads REQUIRED)
set(wxWidgets_ROOT_DIR "/usr/local/lib/wx")
find_package(wxWidgets REQUIRED COMPONENTS core base xml xrc html gl)

include(${wxWidgets_USE_FILE})


file(GLOB SRC2 "${LIBRARY_DIR}/include/*")
include_directories(${SRC2} ${SRC_DIR} ${wxWidgets_INCLUDE_DIRS})
link_directories(${LIBRARY_DIR}/lib/glfw ${LIBRARY_DIR}/lib/wxWidhets ${LIBRARY_DIR}/lib/xml)
		

foreach(what ${SRC2})
    message(${what})
endforeach()



file(GLOB_RECURSE SRC "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")
add_executable(testbuild ${SRC} ${GLAD})

#target_include_directories(testbuild PRIVATE ${LIBRARY_DIR}/include/*)

target_link_libraries(testbuild PRIVATE  dl Threads::Threads libglfw3.a libtinyxml2.a ${wxWidgets_LIBRARIES})



target_compile_definitions(testbuild PRIVATE ${wxWidgets_DEFINITIONS})
#set_target_properties(testbuild PROPERTIES COMPILE_FLAGS "-m64 -march=native")

cmake_minimum_required(VERSION 3.25)

project (FileMungus VERSION 1.0 LANGUAGES CXX C)
#find_package(wxWidgets REQUIRED COMPONENTS core base std richtext propgrid adv)

list(APPEND SOURCES
    src/main.cpp
    src/FileMungusApp.cpp
    src/FileMungusMainWindow.cpp
    src/TopPanel.cpp
    src/FileView.cpp
    src/SidePanel.cpp
    src/FileMungusPathLogic.cpp
    src/resource.cpp
    src/FileMenu.cpp
    src/RenameDialog.cpp
    src/CustomDialog.cpp
    src/CreateDialog.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1) 

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")



#include(${wxWidgets_USE_FILE})
add_executable(FileMungus ${SOURCES})
target_include_directories(FileMungus PUBLIC include)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectLibs.cmake)
if (WIN32)
    target_link_libraries(FileMungus PRIVATE wx::core wx::base wx::richtext wx::propgrid wx::adv wx::xrc)
    #target_include_directories(FileMungus PRIVATE ${wxWidgets_SOURCE_DIR}/include)
    #add_subdirectory(${wxWidgets_SOURCE_DIR})
else()
    target_link_libraries(FileMungus ${wxWidgets_LIBRARIES} nlohmann)
endif()

target_compile_options(FileMungus PRIVATE "$<${gcc_like_cxx}:-Wall;-Wextra;-Wconversion;-std=c++17>"  
                                                        "$<${msvc_cxx}:/W3;/std:c++17>")

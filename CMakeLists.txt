cmake_minimum_required(VERSION 3.25)

project (FileMungus VERSION 1.0 LANGUAGES CXX C)
find_package(wxWidgets REQUIRED COMPONENTS core base std richtext propgrid adv)

list(APPEND SOURCES
    src/main.cpp
    src/FileMungusApp.cpp
    src/FileMungusMainWindow.cpp
    src/TopPanel.cpp
    src/FileView.cpp
    src/SidePanel.cpp
    src/FileMungusPathLogic.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1) 

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

include(${wxWidgets_USE_FILE})
add_executable(FileMungus ${SOURCES})
target_include_directories(FileMungus PUBLIC include)

if (WIN32)
    target_link_libraries(FileMungus PRIVATE wx::core wx::base wx::std wx::richtext wx::propgrid wx::adv)
else()
    target_link_libraries(FileMungus PRIVATE ${wxWidgets_LIBRARIES})
endif()

target_compile_options(FileMungus PRIVATE "$<${gcc_like_cxx}:-Wall;-Wextra;-Wconversion;-std=c++17>"  
                                                        "$<${msvc_cxx}:/W3;/std:c++17>")

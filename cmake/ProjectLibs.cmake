if(NOT WIN32)
    set(CPM_LOCAL_PACKAGES_ONLY True)
    set(CPM_USE_LOCAL_PACKAGES True)
endif()

set(CPM_SOURCE_CACHE ${CMAKE_CURRENT_LIST_DIR}/third_party/CPM)
include(${CMAKE_CURRENT_LIST_DIR}/FetchCPM.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/CPM.cmake)
CPMAddPackage(NAME wxWidgets
    GITHUB_REPOSITORY wxWidgets/wxWidgets
    VERSION 3.2.0
    GIT_TAG v3.2.0    
    OPTIONS
        "wxBUILD_SHARED FALSE"
        "wxBUILD_OPTIMISE ON"
    )

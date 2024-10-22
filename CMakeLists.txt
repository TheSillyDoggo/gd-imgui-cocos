cmake_minimum_required(VERSION 3.14)

project(imgui-cocos)

add_library(imgui-cocos INTERFACE)

set_target_properties(imgui-cocos PROPERTIES CXX_VISIBILITY_PRESET hidden)

target_sources(imgui-cocos INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/backend.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hooks.cpp
)

target_include_directories(imgui-cocos INTERFACE include)

option(HAS_IMGUI "If imgui is already provided externally" OFF)
set(IMGUI_VERSION "v1.88" CACHE STRING "What imgui version to download and use")

if (NOT HAS_IMGUI)
    if (NOT COMMAND CPMAddPackage)
        include(cmake/CPM.cmake)
    endif()

    CPMAddPackage("gh:ocornut/imgui#${IMGUI_VERSION}")

    add_definitions(-DIMGUI_ENABLE_FREETYPE)

    target_include_directories(imgui-cocos INTERFACE ${imgui_SOURCE_DIR})

    target_sources(imgui-cocos INTERFACE
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
        ${imgui_SOURCE_DIR}/misc/freetype/imgui_freetype.cpp
    )

    CPMAddPackage("gh:freetype/freetype2#0ae7e60")

    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build FreeType as a static library" FORCE)

    target_include_directories(imgui-cocos INTERFACE ${freetype2_SOURCE_DIR}/include)
    target_link_libraries(imgui-cocos INTERFACE freetype)
endif()

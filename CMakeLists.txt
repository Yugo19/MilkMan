cmake_minimum_required(VERSION 3.5)

project(MilkManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_USE_QTSQL TRUE)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.3.1\\mingw_64")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql PrintSupport Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        welcom.h
        welcom.cpp
        welcom.ui
        server.h
        server.cpp
        mainmenu.h
        mainmenu.cpp
        mainmenu.ui
        ventes.h
        ventes.cpp
        ventes.ui
        enregistrements.h
        enregistrements.cpp
        enregistrements.ui
        users.h
        users.cpp
        users.ui
        statistiques.h
        statistiques.cpp
        statistiques.ui
        facture.h
        facture.cpp
        facture.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MilkManager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MilkManager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MilkManager SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MilkManager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

include_directories(${QT_QTSQL_INCLUDE_DIR})
target_link_libraries(MilkManager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MilkManager PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(MilkManager PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(MilkManager PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS MilkManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MilkManager)
endif()

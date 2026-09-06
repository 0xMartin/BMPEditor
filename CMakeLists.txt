cmake_minimum_required(VERSION 3.5)

project(BMPEditor VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.h
        src/mainwindow.cpp
        src/mainwindow.ui
        src/about.ui
        src/about.h
        src/about.cpp
        src/base/rgb.h
        src/base/rgb.cpp
        src/base/error.h
        src/base/error.cpp
        src/base/image.h
        src/base/image.cpp
        src/base/threadrunner.h
        src/base/threadrunner.cpp
        src/base/bmpio.h
        src/base/bmpio.cpp
        src/base/imageutils.h
        src/base/imageutils.cpp
        src/base/formatter.h
        src/base/formatter.cpp
        src/base/steganography.h
        src/base/steganography.cpp
        src/struct/bmpstruct.h
        src/struct/bmpstruct.cpp
        src/image/bmpimage.h
        src/image/bmpimage.cpp
        src/editor/workspace.h
        src/editor/workspace.cpp
        src/editor/mouseeventhelper.h
        src/editor/mouseeventhelper.cpp
        src/editor/imageinfopanel.h
        src/editor/imageinfopanel.cpp
        src/editor/tablewidget.h
        src/editor/tablewidget.cpp
        src/editor/clickablelabel.h
        src/editor/clickablelabel.cpp
        src/editor/imagehistogramwidget.h
        src/editor/imagehistogramwidget.cpp
        src/editor/framewidget.h
        src/editor/framewidget.cpp
        src/dialog/blurdialog.h
        src/dialog/blurdialog.cpp
        src/dialog/brightnessdialog.h
        src/dialog/brightnessdialog.cpp
        src/dialog/contrastdialog.h
        src/dialog/contrastdialog.cpp
        src/dialog/colorbalancedialog.h
        src/dialog/colorbalancedialog.cpp
        src/dialog/writemessagedialog.h
        src/dialog/writemessagedialog.cpp
        src/dialog/kernelinputdialog.h
        src/dialog/kernelinputdialog.cpp
        src/dialog/resizedialog.h
        src/dialog/resizedialog.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BMPEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/resource.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BMPEditor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BMPEditor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BMPEditor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BMPEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BMPEditor)
endif()
set_target_properties(BMPEditor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS BMPEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BMPEditor)
endif()

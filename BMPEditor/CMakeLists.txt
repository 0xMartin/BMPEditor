cmake_minimum_required(VERSION 3.5)

project(BMPEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.h
        mainwindow.cpp
        mainwindow.ui
        about.ui
        about.h
        about.cpp
        Base/rgb.h
        Base/rgb.cpp
        Base/error.h
        Base/error.cpp
        Base/image.h
        Base/image.cpp
        Base/threadrunner.h
        Base/threadrunner.cpp
        Base/bmpio.h
        Base/bmpio.cpp
        Base/imageutils.h
        Base/imageutils.cpp
        Base/formatter.h
        Base/formatter.cpp
        Base/steganography.h
        Base/steganography.cpp
        Struct/bmpstruct.h
        Struct/bmpstruct.cpp
        Image/bmpimage.h
        Image/bmpimage.cpp
        Editor/workspace.h
        Editor/workspace.cpp
        Editor/mouseeventhelper.h
        Editor/mouseeventhelper.cpp
        Editor/imageinfopanel.h
        Editor/imageinfopanel.cpp
        Editor/tablewidget.h
        Editor/tablewidget.cpp
        Editor/clickablelabel.h
        Editor/clickablelabel.cpp
        Editor/imagehistogramwidget.h
        Editor/imagehistogramwidget.cpp
        Editor/framewidget.h
        Editor/framewidget.cpp
        Dialog/blurdialog.h
        Dialog/blurdialog.cpp
        Dialog/brightnessdialog.h
        Dialog/brightnessdialog.cpp
        Dialog/contrastdialog.h
        Dialog/contrastdialog.cpp
        Dialog/colorbalancedialog.h
        Dialog/colorbalancedialog.cpp
        Dialog/writemessagedialog.h
        Dialog/writemessagedialog.cpp
        Dialog/kernelinputdialog.h
        Dialog/kernelinputdialog.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BMPEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resource.qrc
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

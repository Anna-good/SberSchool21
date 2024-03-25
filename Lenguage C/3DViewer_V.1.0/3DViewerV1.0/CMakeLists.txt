cmake_minimum_required(VERSION 3.5)

project(3DViewer1_0 VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)

add_definitions(-DGL_SILENCE_DEPRECATION)

set(PROJECT_SOURCES
        front/main.cpp
        front/MainWindow/mainwindow.cpp
        front/MainWindow/mainwindow.h
        front/MainWindow/mainwindow.ui
        front/OpenGl/glwidget.h
        front/OpenGl/glwidget.cpp
        back/s21_3d_viewer.h
        back/s21_affine.c
        back/s21_obj_file.c
        front/QtGifImage/src/3rdParty/giflib/gif_err.c
        front/QtGifImage/src/3rdParty/giflib/dgif_lib.c
        front/QtGifImage/src/3rdParty/giflib/egif_lib.c
        front/QtGifImage/src/3rdParty/giflib/gif_hash.c
        front/QtGifImage/src/3rdParty/giflib/gifalloc.c
        front/QtGifImage/src/3rdParty/giflib/quantize.c
        front/QtGifImage/src/gifimage/qgifimage.h
        front/QtGifImage/src/gifimage/qgifimage_p.h
        front/QtGifImage/src/gifimage/qgifimage.cpp
        resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer1_0
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3DViewer1_0 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewer1_0 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer1_0
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(3DViewer1_0 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3DViewer1_0 PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(3DViewer1_0 PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(3DViewer1_0 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

set_target_properties(3DViewer1_0 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer1_0)
endif()

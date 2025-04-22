cmake_minimum_required(VERSION 3.16)

project(ChatClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 添加chat下源文件
include_directories(${PROJECT_SOURCE_DIR}/chat)
FILE(GLOB_RECURSE CHAT_HEADER_FILES ${PROJECT_SOURCE_DIR}/chat/*.h)
aux_source_directory(${PROJECT_SOURCE_DIR}/chat CHAT_SOURCE_FILES)

# 添加component下源文件
include_directories(${PROJECT_SOURCE_DIR}/component)
FILE(GLOB_RECURSE COMPONENT_HEADER_FILES ${PROJECT_SOURCE_DIR}/component/*.h)
aux_source_directory(${PROJECT_SOURCE_DIR}/component COMPONENT_SOURCE_FILES)

# 添加login下源文件
include_directories(${PROJECT_SOURCE_DIR}/login)
FILE(GLOB_RECURSE LOGIN_HEADER_FILES ${PROJECT_SOURCE_DIR}/login/*.h)
aux_source_directory(${PROJECT_SOURCE_DIR}/login LOGIN_SOURCE_FILES)

# 添加framelesswindow下源文件
include_directories(${PROJECT_SOURCE_DIR}/framelesswindow)
FILE(GLOB_RECURSE FRAMELESS_HEADER_FILES ${PROJECT_SOURCE_DIR}/framelesswindow/*.h)
aux_source_directory(${PROJECT_SOURCE_DIR}/framelesswindow FRAMELESS_SOURCE_FILES)

set(PROJECT_SOURCES
        main.cpp
        graphicmanager.h graphicmanager.cpp
        ${CHAT_HEADER_FILES} ${CHAT_SOURCE_FILES}
        ${COMPONENT_HEADER_FILES} ${COMPONENT_SOURCE_FILES}
        ${LOGIN_HEADER_FILES} ${LOGIN_SOURCE_FILES}
        ${FRAMELESS_HEADER_FILES} ${FRAMELESS_SOURCE_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ChatClient
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        res.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ChatClient APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ChatClient SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ChatClient
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ChatClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ChatClient)
endif()
set_target_properties(ChatClient PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ChatClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ChatClient)
endif()

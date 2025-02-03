project(UserManagement VERSION 0.1 LANGUAGES CXX)

include(GNUInstallDirs)
include(GenerateExportHeader)  # GenerateExportHeader 모듈 포함

#Headers
set(PRIVATE_HEADERS
    inc/AddUserDialog.h
    inc/loginWin.h
    inc/MainWindow.h
    inc/User.h
    inc/UserDatabase.h
    inc/UserManager.h
    inc/UserTreewidget.h
    inc/SessionManager.h
)

#Sources
set(SOURCES
    src/AddUserDialog.cpp
    src/loginWin.cpp
    src/MainWindow.cpp
    src/User.cpp
    src/UserDatabase.cpp
    src/UserManager.cpp
    src/UserTreewidget.cpp
    src/SessionManager.cpp
)

#UI
set(SOURCES_UI
    ui/AddUserDialog.ui
    ui/LoginWin.ui
    ui/MainWindow.ui
    ui/UserTreeWidget.ui
)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(RESOURCE
    ${CMAKE_SOURCE_DIR}/Resources/style/qdarkstyle/style.qrc
)

# To make the library
# To make .lib change to STATIC
add_library(${PROJECT_NAME} SHARED
    ${PRIVATE_HEADERS}
    ${SOURCES_UI}
    ${SOURCES}
    ${RESOURCE}
)

source_group("ui" FILES ${SOURCES_UI})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:inc>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ui
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        AUTOMOC ON
        AUTORCC ON
        AUTOUIC ON
        AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Core
        Qt5::Widgets
)

target_compile_features(${PROJECT_NAME} 
    PUBLIC 
        cxx_std_17
)

target_compile_options(${PROJECT_NAME}
    PUBLIC
        $<$<COMPILE_LANGUAGE:C>:/wd4251>
        $<$<COMPILE_LANGUAGE:CXX>:/wd4251>
)

# For the shared library
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "build/UserManagement")

generate_export_header(${PROJECT_NAME}
    EXPORT_MACRO_NAME ${PROJECT_NAME}_API
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Export.h
)

# 'make install' to the correct locations
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT dev
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT dev
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT application_userManagement)
install(DIRECTORY inc/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT application_userManagement)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT ${PROJECT_NAME}Config DESTINATION share/${PROJECT_NAME}/cmake COMPONENT dev)

# This makes the project importable from the build directory
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)

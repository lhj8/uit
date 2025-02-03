project(Simulator VERSION 0.1 LANGUAGES CXX)

include(GNUInstallDirs)
include(GenerateExportHeader)

#Headers
set(PRIVATE_HEADERS
    inc/MainWindow.h
)

#Sources
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
)

#UI
set(SOURCES_UI
    ui/MainWindow.ui
)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(RESOURCE
    ${CMAKE_SOURCE_DIR}/Resources/style/qdarkstyle/style.qrc
)

set(UserManagement_DIR "${CMAKE_SOURCE_DIR}/UserManagement")
set(UserManagement_INCLUDE_DIRS "${UserManagement_DIR}/inc")
set(UserManagement_LIBRARIES "${CMAKE_SOURCE_DIR}/build/lib/Debug/UserManagement.lib")

# To make the .exe
add_executable(${PROJECT_NAME}
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
        ${UserManagement_INCLUDE_DIRS}
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
        ${UserManagement_LIBRARIES}
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


# For the .exe
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "build/Simulator")



# 'make install' to the correct locations
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT dev
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT dev
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT application_simulator)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT ${PROJECT_NAME}Config DESTINATION share/${PROJECT_NAME}/cmake COMPONENT dev)

# This makes the project importable from the build directory
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)

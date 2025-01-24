cmake_minimum_required(VERSION 3.16)

project(usermanage VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)   # MOC 자동 활성화
set(CMAKE_AUTOUIC ON)   # UI 자동 활성화
set(CMAKE_AUTORCC ON)   # 리소스 자동 활성화

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# file(GLOB_RECURSE SOURCES
#     "${CMAKE_SOURCE_DIR}/*.cpp"
#     "${CMAKE_SOURCE_DIR}/*.h"
#     "${CMAKE_SOURCE_DIR}/*.ui"
# )


find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(usermanage 
    MainWindow.ui       
    User.h            
    UserManager.h    
    LogInWidget.ui  
    SessionManager.cpp  
    UserDatabase.cpp  
    main.cpp
    MainWindow.cpp  
    SessionManager.h    
    UserDatabase.h    
    loginwidget.cpp        
    MainWindow.h   
    User.cpp            
    UserManager.cpp   
    loginwidget.h
    UserTreeWidget.ui
    UserTreewidget.h 
    UserTreewidget.cpp
)

target_link_libraries(usermanage PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)

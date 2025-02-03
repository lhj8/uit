cmake_minimum_required(VERSION 3.28)
project(HTRUserManagement VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
	# `stdext::checked_array_iterator` 디프리케이션 에러 발생. Qt, Protobuf(added via OpenCV)에 영향을 줌.
	# TODO(TOMA-2737): 미래에는  C++20 hash/span 기반 함수를 사용한 버젼으로 업데이트. `stdext`너무 많이 바뀜.
	add_definitions(-D_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)
	# -D_CRT_SECURE_NO_WARNINGS 도 나중에 윈도우 기반 오래된 라이브러리에서 필요할수 있음.
	add_link_options(/debug)
	# Debug Information Format
	add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/Zi>)
endif()

# 디버그 빌드와 릴리스 빌드를 위한 출력 디렉토리 설정
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)

# 라이브러리 및 아카이브 디렉토리 설정
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE	${CMAKE_BINARY_DIR}/lib/Release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG	${CMAKE_BINARY_DIR}/lib/Debug)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Qt5 COMPONENTS Core Gui Widgets UiTools Charts REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set_property(GLOBAL PROPERTY AUTOGEN_TARGETS_FOLDER "AutoMoc Files")

add_subdirectory(UserManagement)
add_subdirectory(Simulator)
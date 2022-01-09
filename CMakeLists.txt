cmake_minimum_required(VERSION 3.1.3)

# ===== PROJECT CONFIG =====
project(process_edit VERSION 1.2.0)
project(process_edit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_AUTOMOC ON)

add_definitions(-DNODE_EDITOR_STATIC)
# ===== PROJECT OPTIONS =====
option(BUILD_THIRDPARTY "Build third party dependencies" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(BUILD_TESTING "Build UniTest" OFF)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	set( CMAKE_CXX_FLAGS_RELEASE "/MD /Zi /O2 /Ob1 /D NDEBUG")
	set( CMAKE_C_FLAGS_RELEASE "/MD /Zi /O2 /Ob1 /D NDEBUG")

	add_definitions( -D__STDC_LIMIT_MACROS )

  #  set_property(TARGET  APPEND PROPERTY LINK_FLAGS /DEBUG)

ENDIF(CMAKE_SYSTEM_NAME MATCHES "Windows")

# ===== CLONE AND INSTALL DEPENDENCIES =====

# =====  FIND PACK =====
find_package(Qt5 COMPONENTS Core Gui Widgets PrintSupport REQUIRED)

# ===== CREATE LIBRARY FROM SOURCE =====

# ===== HEAD FILE =====
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/opencv)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/nodeediter/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/opencv/include)

# ===== SOURCE FILE =====
file(GLOB LIB_SRC 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

file(GLOB LIB_OPENCV
	"${CMAKE_CURRENT_SOURCE_DIR}/src/opencv/*.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/opencv/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/opencv/*.hpp")

# ===== SOURCE GROUP =====
source_group("common" FILES ${LIB_SRC})
source_group("opencv model" FILES ${LIB_OPENCV})

# ===== LIKN DIRECTORY =====
link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/nodeediter/lib
	${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/opencv/lib)

# ===== LINK LIBRARY =====
link_libraries(Qt5::Core Qt5::Gui Qt5::Widgets Qt5::PrintSupport)

link_libraries(debug opencv_world452d)
link_libraries(debug nodesd)

link_libraries(optimized opencv_world452)
link_libraries(optimized nodes)

# ===== CREATE LIBRARY =====
add_library(${PROJECT_NAME} STATIC ${LIB_SRC} ${LIB_OPENCV})

# ===== Test =====
# Use add_test(<executable target>) to run an executable with "make test" CTest
# automatically creates a BUILD_TESTING option (default ON). Note: This should
# be called from the top level CMakeLists.txt

include(CTest)

if(${BUILD_TESTING})
	# create executable from source
	# add_executable(opencv_test ${CMAKE_CURRENT_SOURCE_DIR}/test/opencv_test.cc)
	add_executable(basenode_test ${CMAKE_CURRENT_SOURCE_DIR}/test/basenode_test.cc)
	target_link_libraries(basenode_test ${PROJECT_NAME})

	add_executable(opencv_test ${CMAKE_CURRENT_SOURCE_DIR}/test/opencv_test.cc)
	target_link_libraries(opencv_test ${PROJECT_NAME})
	# link the libraries
#	target_link_libraries(ethcat_test ${PROJECT_NAME})
endif()

ADD_SUBDIRECTORY(app/opencv_process_edit)

# ===== IDE CONFIGURATION =====
IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
	link_libraries(pthread)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(CMAKE_CXX_FLAGS_RELEASE "/Zi /Od /DEBUG") #release
	set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od /DEBUG") #debug
	target_link_libraries(${PROJECT_NAME} ws2_32 winmm)
	ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)
ELSE()
	MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
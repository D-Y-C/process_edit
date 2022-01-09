cmake_minimum_required (VERSION 3.8)

project ("flexiv_wsb_software")

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ===== FIND PACK ===== 
find_package(Qt5 COMPONENTS Core Widgets PrintSupport Network 3DCore 3DRender 3DInput 3DExtras Gui  REQUIRED)

# ==== QT SROUCE FILE & QT UI ===== #
set(QRC_SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/gui/fancydemo.qrc
	${CMAKE_CURRENT_SOURCE_DIR}/gui/qcanpool/qcanpool.qrc
)

qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

# ===== HEAD FILES ===== 
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/client
	${CMAKE_CURRENT_SOURCE_DIR}/client/protobuf-c
	${CMAKE_CURRENT_SOURCE_DIR}/gui
	${CMAKE_CURRENT_SOURCE_DIR}/gui/qcanpool
	${CMAKE_CURRENT_SOURCE_DIR}/gui/customplot
	)

# ===== SOURCE FILES ===== 
file(GLOB MAIN_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB GUI_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/gui/*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/gui/*.h")
file(GLOB GUI_QCANPOOL_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/gui/qcanpool/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/gui/qcanpool/*.h")
file(GLOB GUI_CUSTOMPLOT_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/gui/customplot/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/gui/customplot/*.h")
file(GLOB CLIENT_SRC_FILES 
		"${CMAKE_CURRENT_SOURCE_DIR}/client/*.cc" 
		"${CMAKE_CURRENT_SOURCE_DIR}/client/*.c" 
		"${CMAKE_CURRENT_SOURCE_DIR}/client/*.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/client/protobuf-c/*.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/client/protobuf-c/*.c"
		)
	
source_group(gui FILES ${GUI_SRC_FILES})
source_group("gui/qcanpool" FILES ${GUI_QCANPOOL_SRC_FILES})
source_group("gui/customplot" FILES ${GUI_CUSTOMPLOT_SRC_FILES})
source_group("Resource File" FILES ${QRC_SOURCE_FILES})
source_group("client" FILES ${CLIENT_SRC_FILES})

# ===== LINK LIBRARY ===== 
link_libraries(
Qt5::Core Qt5::Widgets Qt5::Gui  Qt5::PrintSupport Qt5::Network
Qt5::3DCore Qt5::3DRender Qt5::3DInput Qt5::3DExtras
)

# ===== EXECUTE APPLICATION ====== 
add_executable(
 	${PROJECT_NAME}
	${MAIN_SRC_FILES}
	${MAIN_WINDOW}
	${QRC_FILES}
	${GUI_SRC_FILES}
	${GUI_QCANPOOL_SRC_FILES}
	${GUI_CUSTOMPLOT_SRC_FILES}
	${CLIENT_SRC_FILES}
)

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
	link_libraries(pthread)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(CMAKE_CXX_FLAGS_RELEASE "/Zi /Od /DEBUG") #release
	set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od /DEBUG") #debug°æ
	target_link_libraries(${PROJECT_NAME} ws2_32 winmm)
	ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)
ELSE()
	MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
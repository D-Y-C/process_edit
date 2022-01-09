# use cmake 3 which supports targets
cmake_minimum_required(VERSION 3.1.3)

# ===== PROJECT CONFIG =====
project(opencv_process_edit)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#add_definitions(-DNODE_EDITOR_SHARED)


# =====  STD =====
set(CMAKE_CXX_STANDARD 17)
 
# =====  FIND PACK =====
find_package(Qt5 COMPONENTS Core Widgets PrintSupport Network 3DCore 3DRender 3DInput 3DExtras Gui  REQUIRED)

# ==== QT SROUCE FILE & QT UI ===== #
set(QRC_SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/gui/fancydemo.qrc
	${CMAKE_CURRENT_SOURCE_DIR}/gui/qcanpool/qcanpool.qrc
)

qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

# ===== HEAD FILE =====#
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/gui
	${CMAKE_CURRENT_SOURCE_DIR}/gui/qcanpool
	${CMAKE_CURRENT_SOURCE_DIR}/gui/customplot
	)

# ===== SOURCE FILE =====
file(GLOB MAIN_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB GUI_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/gui/*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/gui/*.h")
file(GLOB GUI_QCANPOOL_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/gui/qcanpool/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/gui/qcanpool/*.h")
file(GLOB GUI_CUSTOMPLOT_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/gui/customplot/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/gui/customplot/*.h")

# ===== SOURCE GROUP =====
source_group(main FILES ${MAIN_SRC_FILES})

source_group(gui FILES ${GUI_SRC_FILES})
source_group("gui/qcanpool" FILES ${GUI_QCANPOOL_SRC_FILES})
source_group("gui/customplot" FILES ${GUI_CUSTOMPLOT_SRC_FILES})
source_group("Resource File" FILES ${QRC_SOURCE_FILES})


# ===== LIKN DIRECTORY =====

#===== EXECUTE APPLICATION =====
add_executable(${PROJECT_NAME} 
	${MAIN_SRC_FILES}
	${MAIN_WINDOW}
	${QRC_FILES}
	${GUI_SRC_FILES}
	${GUI_QCANPOOL_SRC_FILES}
	${GUI_CUSTOMPLOT_SRC_FILES}
)

# ===== LINK LIBRARY =====
target_link_libraries(${PROJECT_NAME} process_edit)

target_link_libraries(${PROJECT_NAME} 
Qt5::Core Qt5::Widgets Qt5::Gui  Qt5::PrintSupport Qt5::Network
Qt5::3DCore Qt5::3DRender Qt5::3DInput Qt5::3DExtras
)



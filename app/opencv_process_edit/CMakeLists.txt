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
#find_package(Qt5 COMPONENTS Core Gui Widgets PrintSupport REQUIRED)

# ===== HEAD FILE =====#[[
#[[
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/pcb_test 
	${CMAKE_CURRENT_SOURCE_DIR}/tool_box
	${CMAKE_CURRENT_SOURCE_DIR}/components
	${CMAKE_CURRENT_SOURCE_DIR}/modbus)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include/ethcat)
]]

# ===== SOURCE FILE =====
file(GLOB MAIN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cc" "./*.h" "./*.hpp")

# ===== SOURCE GROUP =====
source_group(main FILES ${MAIN_FILES})

# ===== LIKN DIRECTORY =====

#===== EXECUTE APPLICATION =====
add_executable(${PROJECT_NAME} ${MAIN_FILES})

# ===== LINK LIBRARY =====
target_link_libraries(${PROJECT_NAME} process_edit)



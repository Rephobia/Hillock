project(Hillock_src LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${HILLOCK_INCLUDE_DIRECTORY})

IF(WIN32)
SET(GUI_TYPE WIN32)
ENDIF(WIN32)

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR} "*.cpp")
file(GLOB_RECURSE headers
    "${HILLOCK_INCLUDE_DIRECTORY}/*.h"
    "${HILLOCK_INCLUDE_DIRECTORY}/*.hpp")

add_executable(${PROJECT_NAME} ${GUI_TYPE} ${sources} ${headers}
               ${CMAKE_SOURCE_DIR}/resources/win_resources.rc
               ${CMAKE_SOURCE_DIR}/resources/qt_resources.qrc)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

target_include_directories(${PROJECT_NAME} PUBLIC "${HILLOCK_INCLUDE_DIRECTORY}")

target_compile_options(${PROJECT_NAME} PUBLIC
                       -Wall -Wextra -Werror -Wold-style-cast
                       -Wunreachable-code -Wfatal-errors -pedantic-errors -Winit-self)		       
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
		      OUTPUT_NAME "Hillock")

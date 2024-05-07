cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(CANTesterApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()


if (WIN32)
    # list(FILTER GLOBAL_FILES EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/QtHmi/CAN/linux/*.*" )
    # list(FILTER GLOBAL_FILES EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/QtHmi/PMQ/linux/*.*" )
elseif(UNIX)
    # list(FILTER GLOBAL_FILES EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/QtHmi/CAN/windows/*.*" )
    # list(FILTER GLOBAL_FILES EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/QtHmi/PMQ/windows/*.*" )
    file(COPY ${PROJECT_SOURCE_DIR}/src/CAN/linux/scripts/
         DESTINATION ${PROJECT_BINARY_DIR}/scripts/)
ENDIF()

file(GLOB_RECURSE CAN_FILES CONFIGURE_DEPENDS src/CAN/*.cpp src/CAN/*.h)
qt_add_executable(CANTesterApp src/main.cpp ${CAN_FILES})

qt_add_resources(CANTesterApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

target_link_libraries(CANTesterApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS CANTesterApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# make IDEs aware of the QML import path
set(QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/qml CACHE PATH
    "Path to the custom QML components defined by the project")

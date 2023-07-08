cmake_minimum_required(VERSION 3.2.1)

# Project
project(libmodbus)

# Instruct CMake to run moc & rcc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find QtCore module
find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED  COMPONENTS
    Core Gui Qml Svg QuickControls2 LinguistTools PrintSupport 
)


# Target
add_library(${PROJECT_NAME} SHARED "")

# Includes
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

# Sources
file(GLOB_RECURSE SOURCES "*.h" "*.hpp" "*.cpp" "*.c")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

# Compile resources
target_link_libraries(${PROJECT_NAME}
    PUBLIC Qt5::Core
    Qt5::PrintSupport 
    Qt5::Gui Qt5::Qml Qt5::Quick
)


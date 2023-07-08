cmake_minimum_required(VERSION 3.15)

project(modbust_tester)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("./libmodbus" libmodbus)
include_directories("../libmodbus/include")

add_executable(${PROJECT_NAME} main.cpp ModbusHardware.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE libmodbus)

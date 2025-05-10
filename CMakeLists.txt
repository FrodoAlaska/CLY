cmake_minimum_required(VERSION 3.27)
project(cly)

### Project Variables ###
############################################################
set(CLY_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CLY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CLY_INCLUDES 
  ${CLY_INCLUDE_DIR} 
)
############################################################

### CMake Variables ###
############################################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
############################################################

### Project Sources ###
############################################################
set(CLY_SOURCES 
  ${CLY_SRC_DIR}/main.cpp
)
############################################################

### Final Build ###
############################################################
add_executable(${PROJECT_NAME} ${CLY_SOURCES})
############################################################

### Linking ###
############################################################
target_include_directories(${PROJECT_NAME} PUBLIC BEFORE ${CLY_INCLUDES})
############################################################

### Compiling Options ###
############################################################
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
############################################################

### Library Install ###
############################################################
install(TARGETS ${PROJECT_NAME} cly 
        DESTINATION bin)
############################################################

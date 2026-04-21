cmake_minimum_required(VERSION 3.10)
project(lvgl)
set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------开启项目的宏定义------ #
# ------设置当前项目的编译选项------ #
if(NOT DEFINED CURRENT_PROJECT_NAME)
    #set(CURRENT_PROJECT_NAME "dg-8")
    set(CURRENT_PROJECT_NAME "ebook")
endif()

message(STATUS "当前选择的项目：${CURRENT_PROJECT_NAME}")

#向编译器添加头文件搜索路径
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES("my_app/${CURRENT_PROJECT_NAME}/font")
INCLUDE_DIRECTORIES("my_app/${CURRENT_PROJECT_NAME}/ui")
INCLUDE_DIRECTORIES("my_app/${CURRENT_PROJECT_NAME}/img")

if(CURRENT_PROJECT_NAME STREQUAL "ebook")
    INCLUDE_DIRECTORIES("my_app/${CURRENT_PROJECT_NAME}/ui/")
endif()

file(GLOB_RECURSE INCLUDES "lv_drivers/*.h" "lvgl/demos/*.h"  "lvgl/*.h")    
file(GLOB_RECURSE SOURCES  "lv_drivers/*.c" "lvgl/demos/*.c"  "lvgl/src/*.c")   

# 根据选择的项目自动查找ui下的所有源文件和头文件
file(GLOB_RECURSE UI_INCLUDES 
    "my_app/${CURRENT_PROJECT_NAME}/ui/*.h"  
    "my_app/${CURRENT_PROJECT_NAME}/font/*.h"
    "my_app/${CURRENT_PROJECT_NAME}/img/*.h"   
)     
file(GLOB_RECURSE UI_SOURCES  
    "my_app/${CURRENT_PROJECT_NAME}/ui/*.c"  
    "my_app/${CURRENT_PROJECT_NAME}/font/*.c"
    "my_app/${CURRENT_PROJECT_NAME}/img/*.c"         
)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)              
SET(CMAKE_CXX_FLAGS "-O3")

find_package(SDL2 REQUIRED SDL2)
include_directories(${SDL2_INCLUDE_DIRS})

#定义可执行文件
add_executable(main 
    my_app/${CURRENT_PROJECT_NAME}/main.c mouse_cursor_icon.c  
    ${SOURCES}   
    ${INCLUDES}    
    ${UI_INCLUDES}   
    ${UI_SOURCES}
)
     
#添加宏定义
add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)
  
#链接sdl2库       
target_link_libraries(main PRIVATE SDL2 )  

#添加运行目标
add_custom_target (run COMMAND ${EXECUTABLE_OUTPUT_PATH}/main)

#拷贝SDL2.dll文件到bin目录下
file(COPY SDL2.dll DESTINATION ../bin)                                           
                                            
cmake_minimum_required( VERSION 2.8 )
project(disparity)

set( CMAKE_CXX_COMPILER "g++" )
#set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -march=native -O3" )

# 添加Pangolin依赖
find_package( Pangolin )
include_directories( ${Pangolin_INCLUDE_DIRS} )

# 添加Eigen头文件
include_directories( "/usr/include/eigen3" )

# 寻找OpenCV库
find_package( OpenCV 3 REQUIRED )
# 添加头文件
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(disparity main.cpp)
target_link_libraries( disparity  ${Pangolin_LIBRARIES}
                                  ${OpenCV_LIBS})

install(TARGETS disparity RUNTIME DESTINATION bin)


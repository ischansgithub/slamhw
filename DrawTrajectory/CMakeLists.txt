cmake_minimum_required( VERSION 2.8 )
project(drawtrajectory)

set( CMAKE_CXX_COMPILER "g++" )
#set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -march=native -O3" )

# 为使用 sophus，您需要使用find_package命令找到它
find_package( Sophus REQUIRED )
include_directories( ${Sophus_INCLUDE_DIRS} )

# 添加Pangolin依赖
find_package( Pangolin )
include_directories( ${Pangolin_INCLUDE_DIRS} )

add_executable(drawtrajectory drawtrajectory.cpp)
target_link_libraries( drawtrajectory ${Sophus_LIBRARIES} 
                                      ${Pangolin_LIBRARIES})

install(TARGETS drawtrajectory RUNTIME DESTINATION bin)








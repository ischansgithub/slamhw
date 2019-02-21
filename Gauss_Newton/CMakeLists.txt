project(gauss_newton)

# 添加Eigen头文件
include_directories( "/usr/include/eigen3" )

# 寻找OpenCV库
find_package( OpenCV 3 REQUIRED )
# 添加头文件
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(gauss_newton main.cpp)
target_link_libraries( gauss_newton  ${OpenCV_LIBS})

install(TARGETS gauss_newton RUNTIME DESTINATION bin)

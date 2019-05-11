cmake_minimum_required(VERSION 3.13)
project(EX9)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)


add_executable(line line.cpp)
target_link_libraries(line ${OpenCV_LIBS})
add_executable(circle circle.cpp)
target_link_libraries(circle ${OpenCV_LIBS})
add_executable(houghcircle_param houghcircle_param.cpp)
target_link_libraries(houghcircle_param ${OpenCV_LIBS})
add_executable(identify_ball identify_ball.cpp)
target_link_libraries(identify_ball ${OpenCV_LIBS})
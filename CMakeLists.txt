cmake_minimum_required(VERSION 3.10)
project(AutonomousNavStack)

set(CMAKE_CXX_STANDARD 17)

# Dependencies
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

# Include paths
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(perception/lane_detection)

# Lane Detection Executable (refactored path)
add_executable(lane_detection_runner
    perception/lane_detection/lane_detector.cpp
    perception/lane_detection/video_runner.cpp
)

target_link_libraries(lane_detection_runner ${OpenCV_LIBS})

# EKF Localization
add_executable(ekf_test
    localization/test_ekf.cpp
    localization/ekf_localization.cpp
)
find_package(yaml-cpp REQUIRED)
target_link_libraries(ekf_test Eigen3::Eigen yaml-cpp)

# FSM Planner
add_executable(fsm_test
    planning/fsm_planner.cpp
    planning/test_fsm.cpp
)

target_link_libraries(fsm_test Eigen3::Eigen)
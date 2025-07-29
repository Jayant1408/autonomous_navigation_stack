#ifndef LANE_DETECTOR_HPP
#define LANE_DETECTOR_HPP

#include <opencv2/opencv.hpp>


class LaneDetector{
    public:
        LaneDetector() = default;
        cv::Mat detectLanes(const cv::Mat& frame);
};

#endif
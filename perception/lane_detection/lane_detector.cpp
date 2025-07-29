#include "lane_detector.hpp"

cv::Mat LaneDetector::detectLanes(const cv::Mat& frame)
{
    cv::Mat gray, blur, edges;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, blur, cv::Size(5,5),0);
    cv::Canny(blur, edges, 50, 150);

    cv::Mat mask = cv::Mat::zeros(edges.size(), edges.type());
    std::vector<cv::Point> roi = {
        {0,edges.rows},
        {edges.cols, edges.rows},
        {edges.cols / 2, static_cast<int>(edges.rows * 0.6)}
    };

    cv::fillConvexPoly(mask, roi, 255);
    cv::Mat masked;
    cv::bitwise_and(edges, mask, masked);

    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(masked, lines, 1, CV_PI/180, 50,50, 150);

    cv::Mat line_img = cv::Mat::zeros(frame.size(), frame.type());
    for (const auto& l : lines) {
        cv::line(line_img, {l[0], l[1]}, {l[2], l[3]}, cv::Scalar(0, 255, 0), 3);
    }

    cv::Mat result;
    cv::addWeighted(frame, 0.8, line_img, 1, 0, result);
    return result;



}
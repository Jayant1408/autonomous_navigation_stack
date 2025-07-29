#include "lane_detector.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    std::string input_path = "test_road.jpg";
    std::string output_path = "lane_output.jpg";
    bool is_video = false;

    // Parse arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.rfind("--input=", 0) == 0) {
            input_path = arg.substr(8);
            std::string ext = fs::path(input_path).extension().string();
            std::vector<std::string> video_exts = {".mp4", ".avi", ".mov"};
            for (const auto& ve : video_exts) {
                if (ext == ve) {
                    is_video = true;
                    break;
                }
            }
        } else if (arg.rfind("--output=", 0) == 0) {
            output_path = arg.substr(9);
        }
    }

    LaneDetector detector;

    if (!is_video) {
        // --- Single Image Mode ---
        cv::Mat image = cv::imread(input_path);
        if (image.empty()) {
            std::cerr << "Error: Could not open image " << input_path << "\n";
            return -1;
        }

        // Ensure output folder exists
        fs::path out_path(output_path);
        fs::create_directories(out_path.parent_path());

        cv::Mat result = detector.detectLanes(image);
        cv::imwrite(output_path, result);
        std::cout << "Saved image to: " << output_path << std::endl;

    } else {
        // --- Video Mode ---
        cv::VideoCapture cap(input_path);
        if (!cap.isOpened()) {
            std::cerr << "Error: Could not open video " << input_path << "\n";
            return -1;
        }

        int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
        int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
        double fps = cap.get(cv::CAP_PROP_FPS);
        int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');

        // Ensure output directory exists
        fs::path out_path(output_path);
        fs::create_directories(out_path.parent_path());

        cv::VideoWriter writer;
        writer.open(output_path, fourcc, fps, cv::Size(frame_width, frame_height));

        if (!writer.isOpened()) {
            std::cerr << "Error: Could not open output video file: " << output_path << std::endl;
            return -1;
        }

        std::cout << "Processing video at " << fps << " FPS..." << std::endl;

        cv::Mat frame;
        int frame_idx = 0;

        while (cap.read(frame)) {
            cv::Mat output = detector.detectLanes(frame);
            writer.write(output);
            frame_idx++;
        }

        std::cout << "Saved " << frame_idx << " processed frames to video: " << output_path << std::endl;
    }

    return 0;
}

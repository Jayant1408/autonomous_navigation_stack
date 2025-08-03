#include "trajectory_generator.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <cmath>
#include <iostream>

TrajectoryGenerator::TrajectoryGenerator() {}

std::vector<TrajectoryPoint> TrajectoryGenerator::generateStraightPath(const Eigen::Vector2d& start, double heading, double velocity, int steps)
{
    std::vector<TrajectoryPoint> traj;
    double dt = 0.1;
    for(int i = 0; i < steps; ++i)
    {
        double dx = velocity * dt * i * std::cos(heading);
        double dy = velocity * dt * i * std::sin(heading);
        traj.push_back({start.x() + dx, start.y() + dy, heading, velocity});
    }
    return traj;
}


std::vector<TrajectoryPoint> TrajectoryGenerator::generateStopTrajectory(const Eigen::Vector2d& current_pos)
{
    return {{current_pos.x(), current_pos.y(), 0.0,0.0}};
}


// void TrajectoryGenerator::saveToJson(const std::vector<TrajectoryPoint>& trajectory, const std::string& filename){
//     nlohmann::json j;
//     for(const auto& pt : trajectory)
//     {
//          j.push_back({{"x", pt.x}, {"y", pt.y}, {"heading", pt.heading}, {"velocity", pt.velocity}});
//     }
//     std::ofstream file(filename);
//     file << j.dump(2);
// }

void TrajectoryGenerator::saveToJson(const std::vector<TrajectoryPoint>& trajectory, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Could not open " << filename << " for writing.\n";
        return;
    }

    if (trajectory.empty()) {
        std::cerr << "[WARNING] Attempting to write empty trajectory to JSON.\n";
    }

    nlohmann::json j = nlohmann::json::array();

    for (const auto& pt : trajectory) {
        j.push_back({
            {"x", pt.x},
            {"y", pt.y},
            {"heading", pt.heading},
            {"velocity", pt.velocity}
        });
    }

    file << j.dump(2);  // Pretty print
    file.close();
}
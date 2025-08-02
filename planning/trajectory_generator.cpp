#include "trajectory_generator.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <cmath>

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


void TrajectoryGenerator::saveToJson(const std::vector<TrajectoryPoint>& trajectory, const std::string& filename){
    nlohmann::json j;
    for(const auto& pt : trajectory)
    {
         j.push_back({{"x", pt.x}, {"y", pt.y}, {"heading", pt.heading}, {"velocity", pt.velocity}});
    }
    std::ofstream file(filename);
    file << j.dump(2);
}
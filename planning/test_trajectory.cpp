#include "trajectory_generator.hpp"
#include <Eigen/Dense>
#include <iostream>

int main()
{
    TrajectoryGenerator generator;

    Eigen::Vector2d start(0.0, 0.0);
    double heading = 0.0; // straight ahead
    auto traj = generator.generateStraightPath(start, heading, 1.0, 50);
    generator.saveToJson(traj, "planning/trajectory.json");
    std::cout << "Trajectory saved to planning/trajectory.json\n";
    return 0;
}

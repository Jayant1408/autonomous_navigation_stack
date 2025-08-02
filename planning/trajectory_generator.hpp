#pragma once
#include <vector>
#include  <Eigen/Dense>

struct TrajectoryPoint{
    double x;
    double y;
    double heading;
    double velocity;
};


class TrajectoryGenerator{
    public:
        TrajectoryGenerator();
        std::vector<TrajectoryPoint> generateStraightPath(const Eigen::Vector2d& start, double heading, double velocity, int steps);
        std::vector<TrajectoryPoint> generateStopTrajectory(const Eigen::Vector2d& current_pos);

        void saveToJson(const std::vector<TrajectoryPoint>& trajectory, const std::string& filename);

};
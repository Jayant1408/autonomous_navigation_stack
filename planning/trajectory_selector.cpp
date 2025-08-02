#include "trajectory_generator.hpp"
#include "fsm_planner.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

int main(){
    std::ifstream fsm_file("planning/fsm_log.csv");
    std::string line;
    std::getline(fsm_file, line);

    TrajectoryGenerator generator;
    Eigen::Vector2d pos(0.0,0.0);
    double heading = 0.0;

    std::vector<TrajectoryPoint> full_trajectory;

    while(std::getline(fsm_file, line))
    {
        std::stringstream ss(line);
        std::string step, x_str, y_str, state;
        std::getline(ss, step, ',');
        std::getline(ss, x_str, ',');
        std::getline(ss, y_str, ',');
        std::getline(ss, state, ',');

        pos.x() = std::stod(x_str);
        pos.y() = std::stod(y_str);
        
        std::vector<TrajectoryPoint> traj;

        if(state == "GO_STRAIGHT")
        {
            traj = generator.generateStraightPath(pos, heading, 1.0, 5);
        }
        else
        {
            traj = generator.generateStopTrajectory(pos);
        }

        full_trajectory.insert(full_trajectory.end(), traj.begin(), traj.end());
    }
    generator.saveToJson(full_trajectory, "planning/full_trajectory.json");
    std::cout << "[INFO] Combined trajectory saved to planning/full_trajectory.json\n";
    return 0;
}
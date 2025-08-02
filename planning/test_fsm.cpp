#include "fsm_planner.hpp"
#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <nlohmann/json.hpp>
using namespace Eigen;
using json = nlohmann::json;

std::vector<Obstacle> loadObstaclesfromJson(const std::string& path)
{
    std::ifstream file(path);
    std::vector<Obstacle> obstacles;

    if(!file.is_open())
    {
        std::cerr << "[Error] Failed to open " << path << std::endl;
        return obstacles;
    }

    json data;
    file >> data;
    for(const auto& item : data)
    {
        Obstacle obs;
        obs.x = item["x"].get<double>();
        obs.y = item["y"].get<double>();
        obs.radius = item["radius"].get<double>();
        obstacles.push_back(obs);
    }

    return obstacles;
}

int main() {
    FSMPlanner planner;
    std::ofstream log("../logs/fsm_log.csv");
    log << "step,x,y,state\n";

    // Define obstacles with positions and radii
    std::vector<Obstacle> obstacles;
    obstacles.emplace_back(3.0, 0.0, 1.0);
    obstacles.emplace_back(10.0, 0.0, 1.0);

    // Simulate ego moving forward`
    for (int step = 0; step < 10; ++step) {
        Eigen::Vector3d ego_state(step * 1.0, 0.0, 0.0);  // x, y, theta

        planner.update(ego_state, obstacles);

        std::string state_str = planner.getStateName();
        log << step << "," << ego_state(0) << "," << ego_state(1) << "," << state_str << "\n";

        std::cout << "[Step " << step << "] Ego position: (" 
                  << ego_state(0) << "," << ego_state(1) << ")\n"
                  << "FSM Decision: " << state_str << "\n\n";
    }

    log.close();
    std::cout << "Saved FSM log to: logs/fsm_log.csv" << std::endl;
    return 0;
}

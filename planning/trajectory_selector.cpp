#include "trajectory_generator.hpp"
#include "fsm_planner.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
    std::ifstream fsm_file("../planning/fsm_log.csv");
    if (!fsm_file.is_open()) {
        std::cerr << "[ERROR] Failed to open planning/fsm_log.csv\n";
        return 1;
    }

    std::string line;
    std::getline(fsm_file, line);  // Skip header

    TrajectoryGenerator generator;
    Eigen::Vector2d pos(0.0, 0.0);
    double heading = 0.0;

    std::vector<TrajectoryPoint> full_trajectory;

    while (std::getline(fsm_file, line)) {
        std::stringstream ss(line);
        std::string step, x_str, y_str, state;
        std::getline(ss, step, ',');
        std::getline(ss, x_str, ',');
        std::getline(ss, y_str, ',');
        std::getline(ss, state, ',');

        pos.x() = std::stod(x_str);
        pos.y() = std::stod(y_str);

        std::cout << "[DEBUG] Parsed step=" << step << ", x=" << x_str
                  << ", y=" << y_str << ", state=" << state << "\n";

        std::vector<TrajectoryPoint> traj;
        if (state == "GO_STRAIGHT") {
            traj = generator.generateStraightPath(pos, heading, 1.0, 5);
        } else {
            traj = generator.generateStopTrajectory(pos);
        }

        std::cout << "[DEBUG] Generated " << traj.size()
                  << " points for state: " << state << "\n";

        full_trajectory.insert(full_trajectory.end(), traj.begin(), traj.end());
    }

    if (full_trajectory.empty()) {
        std::cerr << "[WARNING] Attempting to write empty trajectory to JSON.\n";
    }

    generator.saveToJson(full_trajectory, "../planning/full_trajectory.json");
    std::cout << "[INFO] Combined trajectory saved to planning/full_trajectory.json\n";

    return 0;
}

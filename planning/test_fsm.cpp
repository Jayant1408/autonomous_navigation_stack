#include "fsm_planner.hpp"
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    FSMPlanner planner;

    //Simulated ego vehicle state: [x,y,theta]
    Eigen::Vector3d ego_state(0.0,0.0,0.0);

    //Static obstacle in front
    std::vector<Obstacle> obstacles = {
        {5.0,0.5},  // obstacle ahead and slightly to the right
        {10.0,5.0}, // irrelevant obstacle
        {-2.0,-1.0} // behind the car
    };

    for(int i = 0; i < 10; ++i){
        std::cout << "[Step " << i << "] Ego position: (" << ego_state(0) << "," << ego_state(1) << ")\n";
        planner.update(ego_state, obstacles);
        std::cout << "FSM Decision: " << planner.getStateName() << "\n\n";

        // Move ego forward in x
        ego_state(0) += 1.0;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
#include "fsm_planner.hpp"
#include <cmath>
#include <iostream>

FSMPlanner::FSMPlanner() : current_state(FSMState::GO_STRAIGHT) {}

void FSMPlanner::update(const Eigen::Vector3d& ego_state, const std::vector<Obstacle>& obstacles)
{
    const double LOOKAHEAD_DIST = 10.0; // meters
    const double OBSTACLE_THRESH = 2.0; // meters
    bool obstacle_ahead = false;
    for(const auto& obs : obstacles)
    {
        double dx = obs.x - ego_state(0);
        double dy = obs.y - ego_state(1);
        double distance = std::hypot(dx,dy);
        double heading = std::atan2(dy,dx);
        double heading_diff = std::abs(ego_state(2) - heading);

        // Check if obstacle is in front and close
        if(distance < LOOKAHEAD_DIST && heading_diff < M_PI / 6.0)
        {
            obstacle_ahead = true;
            break;
        }
    }
}
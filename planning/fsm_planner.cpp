#include "fsm_planner.hpp"

FSMPlanner::FSMPlanner() : current_state_(FSMState::GO_STRAIGHT) {}

void FSMPlanner::update(const Eigen::Vector3d& ego_state, const std::vector<Obstacle>& obstacles) {
    // Simple rule: if obstacle is within 3m in front, stop
    bool stop_required = false;
    for (const auto& obs : obstacles) {
        double dx = obs.x - ego_state(0);
        double dy = obs.y - ego_state(1);
        if (dx > 0 && dx < 3.0 && std::abs(dy) < 1.0) {
            stop_required = true;
            break;
        }
    }

    switch (current_state_) {
        case FSMState::GO_STRAIGHT:
            if (stop_required)
                current_state_ = FSMState::STOP;
            break;
        case FSMState::STOP:
            if (!stop_required)
                current_state_ = FSMState::GO_STRAIGHT;
            break;
        default:
            current_state_ = FSMState::GO_STRAIGHT;
            break;
    }
}

FSMState FSMPlanner::getCurrentState() const {
    return current_state_;
}

std::string FSMPlanner::getStateName() const {
    switch (current_state_) {
        case FSMState::IDLE: return "IDLE";
        case FSMState::GO_STRAIGHT: return "GO_STRAIGHT";
        case FSMState::TURN_LEFT: return "TURN_LEFT";
        case FSMState::TURN_RIGHT: return "TURN_RIGHT";
        case FSMState::STOP: return "STOP";
        default: return "UNKNOWN";
    }
}

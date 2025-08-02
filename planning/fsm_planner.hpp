#ifndef FSM_PLANNER_HPP
#define FSM_PLANNER_HPP

#include <Eigen/Dense>
#include <string>
#include <vector>
#include <iostream>

// Basic FSM states
enum class FSMState {
    IDLE,
    GO_STRAIGHT,
    TURN_LEFT,
    TURN_RIGHT,
    STOP
};

struct Obstacle {
    double x;
    double y;
    double radius;

    Obstacle() : x(0), y(0), radius(1.0) {}
    Obstacle(double x_, double y_, double r_) : x(x_), y(y_), radius(r_) {} 
};

class FSMPlanner {
public:
    FSMPlanner();

    // Update planner with current ego state and nearby obstacles
    void update(const Eigen::Vector3d& ego_state, const std::vector<Obstacle>& obstacles);

    // Get the current planner decision/state
    FSMState getCurrentState() const;

    // Debug print of decision
    std::string getStateName() const;

private:
    FSMState current_state_;
};

#endif // FSM_PLANNER_HPP

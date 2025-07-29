#ifndef FSM_PLANNER_HPP
#define FSM_PLANNER_HPP

#include <Eigen/Dense>
#include <string>
#include <vector>
#include <iostream>

//Basic FSM states
enum class FSMState {
    IDLE,
    GO_STRAIGHT,
    TURN_LEFT,
    TURN_RIGHT,
    STOP
};

struct Obstacle{
    double x;
    double y;
};

class FSMPlanner{
    public: 
        FSMPlanner();
        
        // Update planner with current ego state and nearby obstacles
        void update(const Eigen::Vector3d& ego_state, const std::vector<Obstacle>& obstacles);

        // Get the currrent planner decision/state
        FSMState getState() const;

        // Debug print of decision
        std::string getStateName() const;

    private:
        FSMState current_state_;

        //Simple logic to determine if we should stop or turn
        bool isObstacleTooClose(const Eigen::Vector3d& ego, const std::vector<Obstacle>* obs);
};


#endif // FSM_PLANNER_HPP

#ifndef EKF_LOCALIZATION_HPP
#define EKF_LOCALIZATION_HPP

#include <Eigen/Dense>
#include <yaml-cpp/yaml.h>

class EKFLocalization{
    public:
        EKFLocalization(const YAML::Node& config);

        void predict(double v, double omega, double dt);
        void update(const Eigen::Vector2d& measurement);

        Eigen::Vector3d getState() const;

    private:
        Eigen::Vector3d state_;            // [x, y, theta]
        Eigen::Matrix3d cov_;              // Covariance matrix
        Eigen::Matrix3d Q_;                // Process noise
        Eigen::Matrix2d R_;                // Measurement noise
};

#endif
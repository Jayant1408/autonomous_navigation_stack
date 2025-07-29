#include "ekf_localization.hpp"
#include <cmath>

// EKFLocalization::EKFLocalization()
// {
//     state_ << 0.0,0.0,0.0;
//     cov_ = Eigen::Matrix3d::Identity() * 0.1;
//     Q_ = Eigen::Matrix3d::Identity() * 0.01;
//     R_ = Eigen::Matrix2d::Identity() * 0.5;
// }

EKFLocalization::EKFLocalization(const YAML::Node& config)
{
    state_ << config["initial_state"]["x"].as<double>(),
              config["initial_state"]["y"].as<double>(),
              config["initial_state"]["theta"].as<double>();

    cov_ = Eigen::Matrix3d::Zero();
    cov_(0, 0) = config["initial_covariance"]["x"].as<double>();
    cov_(1, 1) = config["initial_covariance"]["y"].as<double>();
    cov_(2, 2) = config["initial_covariance"]["theta"].as<double>();

    Q_ = Eigen::Matrix3d::Zero();
    Q_(0, 0) = config["process_noise"]["x"].as<double>();
    Q_(1, 1) = config["process_noise"]["y"].as<double>();
    Q_(2, 2) = config["process_noise"]["theta"].as<double>();

    R_ = Eigen::Matrix2d::Zero();
    R_(0, 0) = config["measurement_noise"]["x"].as<double>();
    R_(1, 1) = config["measurement_noise"]["y"].as<double>();           
}

void EKFLocalization::predict(double v, double omega, double dt)
{
    double theta = state_(2);

    // Motion model
    state_(0) += v * std::cos(theta) * dt;
    state_(1) += v * std::sin(theta) * dt;
    state_(2) += omega * dt;


    //Jacobian of motion model
    Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
    F(0,2) = -v * std::sin(theta) * dt;
    F(1,2) = v * std::cos(theta) * dt;
    cov_ = F * cov_ * F.transpose() + Q_;
}

void EKFLocalization::update(const Eigen::Vector2d& z)
{
    // Measurement model: h(x) = [x;y]

    Eigen::Vector2d h = state_.head<2>();

    Eigen::Matrix<double,2,3> H;
    H.setZero();
    H(0,0) = 1.0;
    H(1,1) = 1.0;


    Eigen::Vector2d y = z - h;
    Eigen::Matrix2d S = H * cov_ * H.transpose() + R_;
    Eigen::Matrix<double,3,2> K = cov_ * H.transpose() * S.inverse();

    state_ = state_ + K * y;
    cov_ = (Eigen::Matrix3d::Identity() - K * H) * cov_;

}

Eigen::Vector3d EKFLocalization::getState() const{
    return state_;
}
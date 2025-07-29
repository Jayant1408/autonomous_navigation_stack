#include "ekf_localization.hpp"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>
#include <random>
#include <iomanip>

int main() {
    // Load config
    YAML::Node config = YAML::LoadFile("../localization/ekf_config.yaml");

    // Create EKF with config
    EKFLocalization ekf(config);

    // Output log file
    std::string log_file = config["log_file"].as<std::string>();
    std::ofstream log(log_file);
    log << "time,x_est,y_est,theta,x_meas,y_meas\n";

    // Simulate motion
    double dt = 0.1;
    double v = 1.0;       // m/s
    double omega = 0.1;   // rad/s

    std::default_random_engine gen;
    std::normal_distribution<double> noise_x(0.0, config["measurement_noise"]["x"].as<double>());
    std::normal_distribution<double> noise_y(0.0, config["measurement_noise"]["y"].as<double>());

    for (int i = 0; i < 50; ++i) {
        double time = i * dt;

        // Predict step
        ekf.predict(v, omega, dt);

        // Simulate noisy GPS-like measurement
        Eigen::Vector3d true_state = ekf.getState(); // for now, treat predicted as ground truth
        Eigen::Vector2d measurement;
        measurement(0) = true_state(0) + noise_x(gen);
        measurement(1) = true_state(1) + noise_y(gen);

        // Update step
        ekf.update(measurement);
        Eigen::Vector3d est = ekf.getState();

        // Log
        log << std::fixed << std::setprecision(5)
            << time << "," << est(0) << "," << est(1) << "," << est(2) << ","
            << measurement(0) << "," << measurement(1) << "\n";
    }

    log.close();
    std::cout << "Saved EKF log to: " << log_file << std::endl;
    return 0;
}



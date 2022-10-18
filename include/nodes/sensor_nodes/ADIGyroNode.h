#pragma once

#include "nodes/NodeManager.h"
#include "api.h"

class ADIGyroNode : public Node {
private:
    pros::ADIGyro m_gyro;
    std::string m_handle_name;

public:
    ADIGyroNode(NodeManager* node_manager, int port, double multiplier, std::string handle_name);

    ADIGyroNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair, double multiplier, std::string handle_name);

    void initialize();

    float getValue();

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIGyroNode();
};

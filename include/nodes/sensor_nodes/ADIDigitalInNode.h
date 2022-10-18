#pragma once

#include "nodes/NodeManager.h"
#include "api.h"

class ADIDigitalInNode : public Node {
private:
    pros::ADIDigitalIn m_digital_in;
    std::string m_handle_name;

public:
    ADIDigitalInNode(NodeManager* node_manager, int port, std::string handle_name);

    ADIDigitalInNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair, std::string handle_name);

    void initialize();

    int getValue();

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIDigitalInNode();
};

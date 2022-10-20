#pragma once

#include "api.h"
#include "nodes/NodeManager.h"

class ADIAnalogOutNode : public Node {

private:
    pros::ADIAnalogOut m_analog_out;
    std::string m_handle_name;

public:
    ADIAnalogOutNode(NodeManager* node_manager, std::string handle_name, int port);

    ADIAnalogOutNode(NodeManager* node_manager, std::string handle_name, pros::ext_adi_port_pair_t port_pair);

    void initialize();

    void setValue(int value);

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIAnalogOutNode();
};
#pragma once

#include "nodes/NodeManager.h"
#include "api.h"

class ADIPotentiometerNode : public Node {
private:
    pros::ADIPotentiometer m_potentiometer;
    std::string m_handleName;

public:
    ADIPotentiometerNode(NodeManager* node_manager, int port, std::string handle_name, pros::adi_potentiometer_type_e pot_type=pros::E_ADI_POT_EDR);

    ADIPotentiometerNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair, std::string handle_name, pros::adi_potentiometer_type_e pot_type=pros::E_ADI_POT_EDR);

    void initialize();

    int getValue();

    double getAngle();

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIPotentiometerNode();
};

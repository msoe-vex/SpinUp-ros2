#pragma once

#include "nodes/NodeManager.h"
#include "api.h"

class ADIEncoderNode : public Node {
private:
    pros::ADIEncoder m_encoder;
    std::string m_handle_name;

public:
    ADIEncoderNode(NodeManager* node_manager, int port_top, int port_bottom, std::string handle_name, bool reverse=false);

    ADIEncoderNode(NodeManager* node_manager, pros::ext_adi_port_tuple_t port_tuple, std::string handle_name, bool reverse=false);

    void initialize();

    int getValue();

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIEncoderNode();
};

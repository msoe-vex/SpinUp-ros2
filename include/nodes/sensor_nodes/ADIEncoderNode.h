#pragma once

#include "nodes/NodeManager.h"
#include "util/Timer.h"
#include "api.h"

class ADIEncoderNode : public Node {
private:
    pros::ADIEncoder m_encoder;
    std::string m_handle_name;
    int m_prevTicks;
    Timer m_timer;

public:
    ADIEncoderNode(NodeManager* node_manager, int port_top, int port_bottom, std::string handle_name, bool reverse=false);

    ADIEncoderNode(NodeManager* node_manager, pros::ext_adi_port_tuple_t port_tuple, std::string handle_name, bool reverse=false);

    void initialize();

    int getValue();

    float getRPM();

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIEncoderNode();
};

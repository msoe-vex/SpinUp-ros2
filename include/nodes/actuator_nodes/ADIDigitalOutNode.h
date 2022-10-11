#pragma once

#include "api.h"
#include "nodes/NodeManager.h"

class ADIDigitalOutNode : public Node {
private:
    pros::ADIDigitalOut m_digital_out;
    std::string m_handle_name;
    bool m_reverse;

    void m_setValue(const std_msgs::Bool& msg);

    void m_publishData(const std_msgs::Empty& msg);

public:
    ADIDigitalOutNode(NodeManager* node_manager, std::string handle_name, int port, bool initial_state=false, bool reverse=false);

    ADIDigitalOutNode(NodeManager* node_manager, std::string handle_name, pros::ext_adi_port_pair_t port_pair, bool initial_state=false, bool reverse=false);

    void initialize();

    void setValue(bool value);

    ~ADIDigitalOutNode();
};
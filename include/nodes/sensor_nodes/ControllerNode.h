#pragma once

#include "api.h"
#include "nodes/NodeManager.h"
#include "pros/misc.h"

class ControllerNode : public Node {
private:
    pros::Controller m_controller; //Creates a new Pros Controller object
    std::string m_handle_name; //Creates a handle name to specify between objects

    // void m_rumbleController(const std_msgs::String& msg);

public:
    ControllerNode(NodeManager* node_manager, std::string handle_name,
        pros::controller_id_e_t controller_id=pros::E_CONTROLLER_MASTER);

    void initialize();

    pros::Controller* getController();

    void teleopPeriodic();

    void autonPeriodic();
    
    int selectorMenu(std::vector<std::string> options);
    void updateDisplay(std::string text);

    ~ControllerNode();
};
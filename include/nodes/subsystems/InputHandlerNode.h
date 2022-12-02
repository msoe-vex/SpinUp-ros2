#pragma once

#include "nodes/NodeManager.h"
#include "nodes/sensor_nodes/ControllerNode.h"
#include "nodes/subsystems/HolonomicDriveNode.h"
#include "pros/misc.h"
#include <cstddef>
#include <unordered_map>



class InputHandlerNode : public Node {
private: 
    pros::Controller* m_controller;
    std::string m_handle_name;

public: 
    const pros::controller_digital_e_t ALL_BUTTONS[12] = {
        pros::E_CONTROLLER_DIGITAL_L1,
        pros::E_CONTROLLER_DIGITAL_L2,
        pros::E_CONTROLLER_DIGITAL_R1,
        pros::E_CONTROLLER_DIGITAL_R2,
        pros::E_CONTROLLER_DIGITAL_A,
        pros::E_CONTROLLER_DIGITAL_B,
        pros::E_CONTROLLER_DIGITAL_X,
        pros::E_CONTROLLER_DIGITAL_Y,
        pros::E_CONTROLLER_DIGITAL_UP,
        pros::E_CONTROLLER_DIGITAL_DOWN,
        pros::E_CONTROLLER_DIGITAL_LEFT,
        pros::E_CONTROLLER_DIGITAL_RIGHT,
    };

    InputHandlerNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller);

    std::unordered_map<pros::controller_digital_e_t, std::nullptr_t> just_pressed;
    std::unordered_map<pros::controller_digital_e_t, std::nullptr_t> pressed;

    void initialize() {};
    void teleopPeriodic();
    void autonPeriodic() {};

    void clear_pressed();

    void push_new_press(pros::controller_digital_e_t button);
    void push_pressing(pros::controller_digital_e_t button);

    ~InputHandlerNode();
};
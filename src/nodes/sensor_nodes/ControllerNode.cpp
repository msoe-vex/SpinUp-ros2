#include "nodes/sensor_nodes/ControllerNode.h"

//This constructor also calls the Node constructor from NodeManager.h
//The Node class constructor automatically adds the node so we don't have to?

//controller_id_e_t is a typedef'ed enum which can be located in the pros/misc.h file
//It can only be E_CONTROLLER_MASTER or E_CONTROLLER_PARTNER 
//CONTROLLER_MASTER and CONTROLLER_PARTNER are #define as their E_ counterparts
ControllerNode::ControllerNode(NodeManager* node_manager, std::string handle_name,
    pros::controller_id_e_t controller_id) : Node(node_manager, 10),
    m_controller(controller_id) {
    m_handle_name = handle_name.insert(0, "joystick/");
}

// void ControllerNode::m_rumbleController(const std_msgs::String& msg) {
//     std::string str = msg.data;
//     if (str.length() <= 8) {
//         m_controller.rumble(str.c_str());
//     }
// }

void ControllerNode::initialize() {
}

pros::Controller* ControllerNode::getController() {
    return &m_controller;
}

void ControllerNode::teleopPeriodic() {
    
}

void ControllerNode::autonPeriodic() {
    
}

// Creates selection menu on controller, returning selected options' position in vector as an int
int ControllerNode::selectorMenu(std::vector<std::string> options) {
    // initial state
    size_t pos = 0;
    std::string option = options.at(pos);
    updateDisplay(option);

    // update loop
    while(!pros::competition::is_connected()) {
        int button_down = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN);
        int button_up = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP);
        if (button_down || button_up) {
            pos += button_down - button_up;

            // bounds checks
            if (pos == options.size()) {
                pos = 0;
            } else if (pos == -1) {
                pos = options.size() - 1;
            }
            
            // update displayed filename
            option = options.at(pos);
            updateDisplay(option);

        } else if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            // return selection
            option = options.at(pos);
            updateDisplay("->" + option);
            return pos;

        } else {
            pros::delay(50);
        }
    }
    return -1;
}

// Refreshes the display and updates it with the given text
void ControllerNode::updateDisplay(std::string text) {
    m_controller.clear_line(0);
    pros::delay(50);
    m_controller.set_text(0, 0, text);
}

ControllerNode::~ControllerNode() {
}
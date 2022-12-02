#include "nodes/subsystems/InputHandlerNode.h"
#include "nodes/NodeManager.h"
#include "pros/misc.h"
#include <string>
#include <unordered_map>

InputHandlerNode::InputHandlerNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller) : 
        Node(node_manager, 10),
        m_controller(controller->getController()) {
    m_handle_name = handle_name.insert(0, "input/");
}

void InputHandlerNode::clear_pressed() {
    just_pressed.clear();
    pressed.clear();
}

void InputHandlerNode::push_new_press(pros::controller_digital_e_t button) {
    just_pressed.insert_or_assign(button, nullptr);
}

void InputHandlerNode::push_pressing(pros::controller_digital_e_t button) {
    pressed.insert_or_assign(button, nullptr);
}

void InputHandlerNode::teleopPeriodic() {
    clear_pressed();

    for (auto button : ALL_BUTTONS) {
        if (m_controller->get_digital_new_press(button)) push_new_press(button);
        if (m_controller->get_digital(button)) push_pressing(button);
    }
}

InputHandlerNode::~InputHandlerNode() {
    
}
#include "nodes/subsystems/LauncherNode.h"

LauncherNode::LauncherNode(NodeManager* node_manager, std::string handle_name, 
		ControllerNode* controller, ADIDigitalOutNode* down_state, ADIDigitalOutNode* up_state,
		pros::controller_digital_e_t manual_button, pros::controller_digital_e_t automatic_button) : 
		IClawNode(node_manager, handle_name), 
		m_controller(controller),
		m_down_state(down_state),
		m_up_state(up_state),
		m_manual_button(manual_button),
		m_automatic_button(automatic_button),
		m_open(true),
		m_manual_previous_state(false){

}

void LauncherNode::initialize() {

}

void LauncherNode::setState(bool up) {
	if (up) {
		m_down_state->setValue(0);
		pros::delay(10);
		m_up_state->setValue(1);
		
	} else {
		m_up_state->setValue(0);
		pros::delay(10);
		m_down_state->setValue(1);
		
	}
}

void LauncherNode::teleopPeriodic() {

	if (m_controller->getController()->get_digital_new_press(m_manual_button)) {
	//&& !m_manual_previous_state) {
		m_open = !m_open;
		setState(m_open);
	}
	
	if (m_controller->getController()->get_digital(m_automatic_button)) {
		setState(true);
		setState(false);
	}

	//m_manual_previous_state = manual_current_state;
}

void LauncherNode::autonPeriodic() {

}

LauncherNode::~LauncherNode() {

}
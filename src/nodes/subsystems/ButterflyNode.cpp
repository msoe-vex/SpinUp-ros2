#include "nodes/subsystems/ButterflyNode.h"
#include "HolonomicDriveNode.h"

ButterflyNode::ButterflyNode(NodeManager* node_manager, std::string handle_name, 
		ControllerNode* controller, ADIDigitalOutNode* claw, pros::controller_digital_e_t button, HolonomicDriveNode* holonomic_drive_node) : 
		IClawNode(node_manager, handle_name), 
		m_controller(controller),
		m_claw(claw),
		m_button(button),
		m_claw_open(false),
		m_a_previous_state(false),
		m_holonomic_drive_node(holonomic_drive_node){

}

void ButterflyNode::initialize() {

}

void ButterflyNode::setState(bool opened) {
	if (opened) {
		m_claw->setValue(0);
		m_holonomic_drive_node->setDriveMode(true);
	} else {
        m_claw->setValue(1);
		m_holonomic_drive_node->setDriveMode(false);
	}
}

void ButterflyNode::teleopPeriodic() {
	bool a_current_state = m_controller->getController()->get_digital(m_button);
	//setState(!a_current_state);

	if (a_current_state == 1 && m_a_previous_state == 0) {
		m_claw_open = !m_claw_open;
		setState(m_claw_open);
	}

	m_a_previous_state = a_current_state;
}

void ButterflyNode::autonPeriodic() {

}

ButterflyNode::~ButterflyNode() {

}
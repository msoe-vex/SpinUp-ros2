#include "nodes/subsystems/ConveyorNode.h"

ConveyorNode::ConveyorNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, 
        MotorNode* bottom_conveyor_motor, MotorNode* top_conveyor_motor, ADIAnalogInNode* bottom_conveyor_sensor, 
        ADIAnalogInNode* top_conveyor_sensor) : Node(node_manager, 5), 
        m_controller(controller->getController()),
        m_bottom_conveyor_motor(bottom_conveyor_motor),  
        m_top_conveyor_motor(top_conveyor_motor), 
        m_bottom_conveyor_sensor(bottom_conveyor_sensor),  
        m_top_conveyor_sensor(top_conveyor_sensor),
        m_enable_holding(false),
        m_previous_ball_on_top(false),
        m_capture_sequence(false) {
    m_handle_name = handle_name.insert(0, "robot/");
}

void ConveyorNode::m_updateConveyorHoldingState(bool top_roller_only) {
    bool is_ball_at_top = (m_top_conveyor_sensor->getValue() <= BALL_PRESENT_THRESHOLD);
    bool is_ball_at_bottom = (m_bottom_conveyor_sensor->getValue() <= BALL_PRESENT_THRESHOLD);

    if (m_capture_sequence) {
        setTopConveyorVoltage(-1 * MAX_MOTOR_VOLTAGE);

        if (m_ball_hold_timer.Get() > 0.05) {
            m_capture_sequence = false;
            m_previous_ball_on_top = true;
            m_ball_hold_timer.Reset();
        }
    } else {
        if (is_ball_at_top && !m_previous_ball_on_top) {
            m_ball_hold_timer.Start();
            m_capture_sequence = true;
            setTopConveyorVoltage(-1 * MAX_MOTOR_VOLTAGE);
        } else if (is_ball_at_top && m_previous_ball_on_top) {
            setTopConveyorVoltage(0);
        } else {
            setTopConveyorVoltage(MAX_MOTOR_VOLTAGE);
            m_previous_ball_on_top = false;
        }
    }

    setBottomConveyorVoltage((is_ball_at_top && is_ball_at_bottom) || top_roller_only ? 0 : MAX_MOTOR_VOLTAGE);
}

void ConveyorNode::setBottomConveyorVoltage(int voltage) {
    m_bottom_conveyor_motor->moveVoltage(voltage);
}

void ConveyorNode::setTopConveyorVoltage(int voltage) {
    m_top_conveyor_motor->moveVoltage(voltage);
}

void ConveyorNode::setConveyorVoltage(int voltage) {
    setTopConveyorVoltage(voltage);
    setBottomConveyorVoltage(voltage);
}

void ConveyorNode::setTopConveyorRPMPercent(float percent) {
    m_top_conveyor_motor->moveVelocity(percent * 600.);
}

void ConveyorNode::setBottomConveyorRPMPercent(float percent) {
    m_bottom_conveyor_motor->moveVelocity(percent * 200.);
}

void ConveyorNode::setConveyorRPMPercent(float percent) {
    setTopConveyorRPMPercent(percent);
    setBottomConveyorRPMPercent(percent);
}

void ConveyorNode::setConveyorState(ConveyorState conveyorState) {
    m_current_conveyor_state = conveyorState;
}

bool ConveyorNode::isBallInTopPosition() {
    return m_top_conveyor_sensor->getValue() <= BALL_PRESENT_THRESHOLD;
}

int ConveyorNode::getNumBallsStored() {
    int ballsStored = 0;

    if (m_bottom_conveyor_sensor->getValue() <= BALL_PRESENT_THRESHOLD) {
        ballsStored++;
    }

    if (m_top_conveyor_sensor->getValue() <= BALL_PRESENT_THRESHOLD) {
        ballsStored++;
    }

    return ballsStored;
}

void ConveyorNode::initialize() {

}

void ConveyorNode::teleopPeriodic() {
    if (m_controller->get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { 
        setConveyorState(SCORING);
    } else if (m_controller->get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        setConveyorState(REVERSE);
    } else if (m_controller->get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
        setConveyorState(DEPLOY);
    } else if (m_controller->get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        setConveyorState(HOLDING);
    } else {
        setConveyorState(STOPPED);
    }

    switch(m_current_conveyor_state) {
        case STOPPED:
            setConveyorVoltage(0);
        break;
        case HOLDING:
            m_updateConveyorHoldingState();
        break;
        case SCORING:
            setConveyorVoltage(MAX_MOTOR_VOLTAGE);
        break;
        case REVERSE:
            setConveyorVoltage(-1 * MAX_MOTOR_VOLTAGE);
        break;
        case DEPLOY:
            setBottomConveyorVoltage(MAX_MOTOR_VOLTAGE);
            setTopConveyorVoltage(0);
        break;
        case SPLIT:
            setConveyorVoltage(0);
        break;
    }
}

void ConveyorNode::autonPeriodic() {
    switch(m_current_conveyor_state) {
        case STOPPED:
            setConveyorVoltage(0);
        break;
        case HOLDING:
            m_updateConveyorHoldingState();
        break;
        case HOLDING_TOP:
            m_updateConveyorHoldingState(true);
        break;
        case SCORING:
            setConveyorVoltage(MAX_MOTOR_VOLTAGE);
        break;
        case SCORING_TOP:
            setTopConveyorVoltage(MAX_MOTOR_VOLTAGE);
            setBottomConveyorVoltage(0);
        break;
        case REVERSE:
            setConveyorVoltage(-1 * MAX_MOTOR_VOLTAGE);
        break;
        case DEPLOY:
            setBottomConveyorVoltage(MAX_MOTOR_VOLTAGE);
            setTopConveyorVoltage(0);
        break;
        case SPLIT:
            setTopConveyorVoltage(MAX_MOTOR_VOLTAGE);
            setBottomConveyorVoltage(-0.5 * MAX_MOTOR_VOLTAGE);
        break;
    }
}

ConveyorNode::~ConveyorNode() {

}
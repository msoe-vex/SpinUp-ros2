#include "lib-rr/auton/Auton.h"

using namespace std;

/*
 * Create a node with given actions and timeout. These actions will all be run in parallel to each other.
 * Nullptrs will not be added as actions, they will be ignored.
 */
AutonNode::AutonNode(double timeout, AutonAction* action1, AutonAction* action2, AutonAction* action3) :
        m_children(), m_actions(), m_timeout(timeout) {
	m_startCondition = nullptr;
    if(action1 != nullptr) {
        m_actions.push_back(action1);
    }
    if(action2 != nullptr) {
        m_actions.push_back(action2);
    }
    if(action3 != nullptr) {
        m_actions.push_back(action3);
    }
}

/*
 * Add a node to this node which will be run sequentially after this node completes all of its actions
 */
void AutonNode::AddNext(AutonNode* childNode) {
    m_children.push_back(childNode);
}

/*
 * Add an action to this node which will be run in parallel to other actions in this node
 */
void AutonNode::AddAction(AutonAction* leaf) {
    if(leaf != nullptr) {
        m_actions.push_back(leaf);
    }
}

/*
 * Add a condition to this node.
 * This condition is passed in as a std::function that will be called to check the condition.
 *
 * Typically, the best way to do this is to create a lambda that contains the code to see if the node should be run.
 *
 * Example:
 * addCondition([]{return shouldNodeRun()});
 *
 * This condition will be checked by the previous node while it is not complete.
 * While it is true this action will run its actions.
 */
void AutonNode::AddCondition(function<bool()> startCondition) {
    m_startConditonGiven = true;
    m_startCondition = startCondition;
}

/*
 * Returns true if all actions are complete and all child nodes are complete or if timeout has been exceeded
 */
bool AutonNode::Complete() {
    if(m_actions.empty()) {
        for(auto child : m_children) {
            if(!child->Complete()) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

/*
 * Prepares node to be run
 */
void AutonNode::Reset() {
    for(auto child : m_children) {
        child->Reset();
    }
    m_actions.clear();
    m_children.clear();
    m_actionsInitialized = false;
}

/*
 * Set the timeout for this node to a given duration in seconds
 */
void AutonNode::SetTimeout(double timeout) {
    m_timeout = timeout;
}

/**
 * Runs all actions in node and checks if child node conditions are true. If they are and this node is not done, that
 * child node is run.
 * @param lastNodeDone If previous node is complete.
 */
void AutonNode::Act(bool lastNodeDone) {
    bool shouldAct = (m_startConditonGiven && m_startCondition && !lastNodeDone)
                     || (!m_startConditonGiven && lastNodeDone);
    if(!m_actionsInitialized && shouldAct) {

        m_timer.Reset();
        m_timer.Start();

        for(auto action : m_actions) {
            action->ActionInit();
        }
        m_actionsInitialized = true;
    }
    if(!m_actions.empty() && (m_timer.Get() > m_timeout)) {
        for(auto action : m_actions) {
            action->ActionEnd();
        }
        for (auto i = m_actions.begin(); i != m_actions.end(); i++){
            delete *i;
        }
        m_actions.clear();
    }
    if(!m_actions.empty()) {
        if(shouldAct) {
            for(unsigned int i = 0; i < m_actions.size(); i++) {
                AutonAction::actionStatus status = m_actions[i]->Action();
                switch(status) {
                    case AutonAction::END:
                        m_actions[i]->ActionEnd();
                        //TODO: There's a memory leak here, need to fix
                        m_actions.erase(m_actions.begin() + i);
                        i--;
                        break;
                    case AutonAction::CONTINUE:
                        break;
                }
            }
            for(auto child : m_children) {
                child->Act(false);
            }
        } else if(m_startConditonGiven && !m_startCondition) {
            return;
        }
    } else {
    	for(auto child : m_children) {
    		child->Act(true);
    	}
    }
}

AutonNode::~AutonNode() {
    for (auto i = m_actions.begin(); i != m_actions.end(); i++){
        delete *i;
    }
    m_actions.clear();
    for (auto i = m_children.begin(); i != m_children.end(); i++){
        delete *i;
    }
    m_children.clear();
}

/*
 * Initialize an autonomous routine with given name, given path, if it needs a path, first node, and whether this autonomous should be the default
 * selected autonomous on Smart Dashboard
 */
Auton::Auton(string name, string path, bool needsPath, bool defaultAuton) {
    m_name = name;
    m_needsPath = needsPath || path == "";
    m_path = path;
    m_defaultAuton = defaultAuton;
}

/*
 * Run autonomous routine. Needs to be called each iteration.
 */
void Auton::AutonPeriodic() {
    for(auto node : m_firstNode) {
        node->Act(true);
    }
}

/*
 * Initialize autonomous routine by resetting and adding all nodes.
 */
void Auton::AutonInit() {
    Reset();
    AddNodes();
}

/*
 * If autonomous routine is complete
 */
bool Auton::Complete() {
    for(auto node : m_firstNode) {
        if(!node->Complete()) {
            return false;
        }
    }
    return true;
}

/*
 * Reset all nodes in autonomous routine
 */
void Auton::Reset() {
    for(auto node : m_firstNode) {
        if(node != nullptr) {
            node->Reset();
        }
    }
}

/*
 * Add another node to be run on start of autonomous routine
 * Nullptrs will not be added as actions, they will be ignored
 */
void Auton::AddFirstNode(AutonNode* firstNode) {
    if(firstNode != nullptr) {
        m_firstNode.push_back(firstNode);
    }
}

/*
 * Returns human readable name of routine
 */
string Auton::GetName() {
    return m_name;
}

/*
 * Returns true if the auton needs a path
 */
bool Auton::GetNeedsPath() {
    return m_needsPath;
}

/*
 * Returns string of path associated with auton
 */
string Auton::GetAssociatedPath() {
    return m_path;
}

/*
 * Automatically deletes all nodes and their actions on deletion of the autonomous routine
 */
Auton::~Auton() {
    for (auto i = m_firstNode.begin(); i != m_firstNode.end(); i++){
        delete *i;
    }
    m_firstNode.clear();
}

/*
 * Takes a duration in seconds to wait for.
 */
WaitAction::WaitAction(double duration) {
	m_duration = duration;
}

void WaitAction::ActionInit() {
	m_timer.Reset();
	m_timer.Start();
}

AutonAction::actionStatus WaitAction::Action() {
	if(m_timer.Get() > m_duration) {
		return AutonAction::END;
	} else {
		return AutonAction::CONTINUE;
	}
}

PrintAction::PrintAction(string toPrint) {
    m_toPrint = toPrint;
}

void PrintAction::ActionInit() {
    cout << m_toPrint << endl;
}

AutonAction::actionStatus PrintAction::Action() {
    return END;
}
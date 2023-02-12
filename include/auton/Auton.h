#pragma once

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <memory>
#include <iostream>
#include <functional>

#include "util/Timer.h"

class AutonAction {
public:
    enum actionStatus {
        CONTINUE,
        END
    };

    virtual void ActionInit() {}

    virtual void ActionEnd() {}

    virtual actionStatus Action() = 0;

    virtual ~AutonAction() {}
};

class AutonNode {
public:
    AutonNode(double timeout, AutonAction* action1 = nullptr, AutonAction* action2 = nullptr, AutonAction* action3 = nullptr);
    void AddNext(AutonNode* childNode);
    void AddAction(AutonAction* leaf);
    void AddCondition(function<bool()> startCondition);
    bool Complete();
    void Reset();
    void SetTimeout(double timeout);
    void Act(bool lastNodeDone);
    ~AutonNode();
private:
    std::vector<AutonNode*> m_children;
    std::vector<AutonAction*> m_actions;
    bool m_startConditonGiven = false;
    bool m_actionsInitialized = false;
    std::function<bool()> m_startCondition;
    double m_timeout;
    Timer m_timer;
};

class Auton {
public:
    Auton(std::string name, std::string path = "", bool needsPath = true, bool defaultAuton = false);

    inline Auton* GetInstance() {
        return this;
    }

    inline bool GetDefault() {
        return m_defaultAuton;
    }

    std::string GetName();
    bool GetNeedsPath();
    std::string GetAssociatedPath();
    void AutonPeriodic();
    void AutonInit();
    bool Complete();
    void Reset();
    virtual ~Auton();
protected:
    void AddFirstNode(AutonNode* firstNode);
    virtual void AddNodes() = 0;
private:
    std::string m_name;
    bool m_needsPath;
    std::string m_path;
    bool m_defaultAuton = false;
    std::vector<AutonNode*> m_firstNode;
};

class WaitAction : public AutonAction {
public:
	WaitAction(double duration);
	void ActionInit();
	actionStatus Action();
private:
	Timer m_timer;
	double m_duration;
};

class PrintAction : public AutonAction {
public:
    PrintAction(std::string toPrint);
    void ActionInit();
    actionStatus Action();

private:
    std::string m_toPrint;
};
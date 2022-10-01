#pragma once

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <memory>
#include <iostream>
#include <functional>

#include "lib-rr/util/Timer.h"

using namespace std;

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
    vector<AutonNode*> m_children;
    vector<AutonAction*> m_actions;
    bool m_startConditonGiven = false;
    bool m_actionsInitialized = false;
    function<bool()> m_startCondition;
    double m_timeout;
    Timer m_timer;
};

class Auton {
public:
    Auton(string name, string path = "", bool needsPath = true, bool defaultAuton = false);

    inline Auton* GetInstance() {
        return this;
    }

    inline bool GetDefault() {
        return m_defaultAuton;
    }

    string GetName();
    bool GetNeedsPath();
    string GetAssociatedPath();
    void AutonPeriodic();
    void AutonInit();
    bool Complete();
    void Reset();
    virtual ~Auton();
protected:
    void AddFirstNode(AutonNode* firstNode);
    virtual void AddNodes() = 0;
private:
    string m_name;
    bool m_needsPath;
    string m_path;
    bool m_defaultAuton = false;
    vector<AutonNode*> m_firstNode;
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
    PrintAction(string toPrint);
    void ActionInit();
    actionStatus Action();

private:
    string m_toPrint;
};
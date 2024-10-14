#pragma once

#include <iostream>
#include <queue>
#include <memory>
#include <vector>

// ����� Action
class Action {
public:
    virtual ~Action() = default; // ����������
    virtual void execute()= 0; // ���麯��������ִ�о��嶯��
};

// ����� Action ����
class ConcreteAction : public Action {
public:
    void execute()override {
        std::cout << "Executing Concrete Action" << std::endl;
    }
};

// ActionQueue �̳��� Action
class ActionQueue : public Action {
private:
    std::queue<std::unique_ptr<Action>> actions; // ʹ�� std::unique_ptr ���� Action ����

public:
    // ���� += ���������������µ� Action ������
    ActionQueue& operator+=(std::unique_ptr<Action> action) {
        actions.push(std::move(action));
        return *this;
    }

    // ��������������Ӳ���
    template<typename T, typename... Args>
    void addAction(Args&&... args) {
        *this += std::make_unique<T>(std::forward<Args>(args)...);
    }

    // ��Ӷ�� Action ����
    template<typename... Args>
    void addActions(Args&&... args) {
        (addAction(std::forward<Args>(args)), ...);
    }

    // ��д execute ����������ִ�ж����е����� Action
    void execute() override {
        while (!actions.empty()) {
            auto & currentAction = actions.front();
            actions.pop();
            currentAction->execute();
        }
    }

    // ��������������ʹ���� std::unique_ptr������Ҫ�ֶ������ڴ�
    ~ActionQueue() = default;
};

// void actions_tb() {
//     ActionQueue queue;
//     queue.addActions<ConcreteAction>(), <ConcreteAction>(), <ConcreteAction>(); // �������Ӷ�� ConcreteAction ʵ��
//     queue.execute(); // ִ�ж����е����ж���
// }
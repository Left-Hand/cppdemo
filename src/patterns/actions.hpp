#pragma once

#include <iostream>
#include <queue>
#include <memory>
#include <vector>

// 虚基类 Action
class Action {
public:
    virtual ~Action() = default; // 虚析构函数
    virtual void execute()= 0; // 纯虚函数，用于执行具体动作
};

// 具体的 Action 子类
class ConcreteAction : public Action {
public:
    void execute()override {
        std::cout << "Executing Concrete Action" << std::endl;
    }
};

// ActionQueue 继承自 Action
class ActionQueue : public Action {
private:
    std::queue<std::unique_ptr<Action>> actions; // 使用 std::unique_ptr 管理 Action 对象

public:
    // 重载 += 运算符，用于添加新的 Action 到队列
    ActionQueue& operator+=(std::unique_ptr<Action> action) {
        actions.push(std::move(action));
        return *this;
    }

    // 辅助函数，简化添加操作
    template<typename T, typename... Args>
    void addAction(Args&&... args) {
        *this += std::make_unique<T>(std::forward<Args>(args)...);
    }

    // 添加多个 Action 对象
    template<typename... Args>
    void addActions(Args&&... args) {
        (addAction(std::forward<Args>(args)), ...);
    }

    // 重写 execute 方法，依次执行队列中的所有 Action
    void execute() override {
        while (!actions.empty()) {
            auto & currentAction = actions.front();
            actions.pop();
            currentAction->execute();
        }
    }

    // 析构函数，由于使用了 std::unique_ptr，不需要手动清理内存
    ~ActionQueue() = default;
};

// void actions_tb() {
//     ActionQueue queue;
//     queue.addActions<ConcreteAction>(), <ConcreteAction>(), <ConcreteAction>(); // 向队列添加多个 ConcreteAction 实例
//     queue.execute(); // 执行队列中的所有动作
// }
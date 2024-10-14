#include <iostream>
#include <vector>
#include <memory>
#include <string>

// 定义一个 Node 类
class Node {
public:
    // 构造函数
    explicit Node(const std::string& name) : name(name) {}

    // 获取节点名称
    const std::string& getName() const { return name; }

    // 添加子节点
    void addChild(std::shared_ptr<Node> child) {
        children.push_back(child);
    }

    // 获取所有子节点
    const std::vector<std::shared_ptr<Node>>& getChildren() const {
        return children;
    }

private:
    std::string name;          // 节点名称
    std::vector<std::shared_ptr<Node>> children;  // 子节点列表
};

// 打印节点及其子节点
void printNode(const std::shared_ptr<Node>& node, int depth = 0) {
    std::cout << std::string(depth * 2, ' ') << "Node: " << node->getName() << std::endl;
    for (const auto& child : node->getChildren()) {
        printNode(child, depth + 1);
    }
}

void tree_tb() {
    // 创建根节点
    auto root = std::make_shared<Node>("Root");

    // 创建子节点
    auto child1 = std::make_shared<Node>("Child1");
    auto child2 = std::make_shared<Node>("Child2");

    // 创建孙子节点
    auto grandchild1 = std::make_shared<Node>("Grandchild1");
    auto grandchild2 = std::make_shared<Node>("Grandchild2");

    // 添加子节点
    root->addChild(child1);
    root->addChild(child2);

    // 添加孙子节点
    child1->addChild(grandchild1);
    child2->addChild(grandchild2);

    // 打印树结构
    printNode(root);

}
#include <iostream>
#include <vector>
#include <memory>
#include <string>

// ����һ�� Node ��
class Node {
public:
    // ���캯��
    explicit Node(const std::string& name) : name(name) {}

    // ��ȡ�ڵ�����
    const std::string& getName() const { return name; }

    // ����ӽڵ�
    void addChild(std::shared_ptr<Node> child) {
        children.push_back(child);
    }

    // ��ȡ�����ӽڵ�
    const std::vector<std::shared_ptr<Node>>& getChildren() const {
        return children;
    }

private:
    std::string name;          // �ڵ�����
    std::vector<std::shared_ptr<Node>> children;  // �ӽڵ��б�
};

// ��ӡ�ڵ㼰���ӽڵ�
void printNode(const std::shared_ptr<Node>& node, int depth = 0) {
    std::cout << std::string(depth * 2, ' ') << "Node: " << node->getName() << std::endl;
    for (const auto& child : node->getChildren()) {
        printNode(child, depth + 1);
    }
}

void tree_tb() {
    // �������ڵ�
    auto root = std::make_shared<Node>("Root");

    // �����ӽڵ�
    auto child1 = std::make_shared<Node>("Child1");
    auto child2 = std::make_shared<Node>("Child2");

    // �������ӽڵ�
    auto grandchild1 = std::make_shared<Node>("Grandchild1");
    auto grandchild2 = std::make_shared<Node>("Grandchild2");

    // ����ӽڵ�
    root->addChild(child1);
    root->addChild(child2);

    // ������ӽڵ�
    child1->addChild(grandchild1);
    child2->addChild(grandchild2);

    // ��ӡ���ṹ
    printNode(root);

}
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class QTreeNode
{
public:
    char data;
    vector<QTreeNode *> children;

    QTreeNode(char value) : data(value) {}
};

class QTree
{
private:
    QTreeNode *root;

public:
    QTree(char rootValue) : root(new QTreeNode(rootValue)) {}

    QTreeNode *addChild(QTreeNode *parent, char childValue)
    {
        QTreeNode *child = new QTreeNode(childValue);
        parent->children.push_back(child);
        return child;
    }

    void showUpsideDown(QTreeNode *node)
    {
        if (node != nullptr)
        {
            cout << node->data;
            vector<QTreeNode *> children = node->children;
            for (int i = 0; i < children.size(); ++i)
            {
                // 2 -> 3 -> 0 -> 1 순서로 접근
                QTreeNode *child = children[(i + 2) % 4];
                showUpsideDown(child);
            }
        }
    }

    QTreeNode *getRoot() const
    {
        return root;
    }
};

int main()
{
    int C;
    cin >> C;

    while (C--)
    {
        string inputs;
        cin >> inputs;

        QTree qtree(inputs[0]);
        vector<QTreeNode *> parentRoots;
        QTreeNode *root = qtree.getRoot();
        for (int i = 1; i < inputs.length(); ++i)
        {
            QTreeNode *child = qtree.addChild(root, inputs[i]);

            if (root->children.size() == 4)
            {
                if (!parentRoots.empty())
                {
                    root = parentRoots.back();
                    parentRoots.pop_back();
                }
            }

            if (inputs[i] == 'x')
            {
                parentRoots.push_back(root);
                root = child;
            }
        }

        qtree.showUpsideDown(root);
        cout << endl;
    }
}
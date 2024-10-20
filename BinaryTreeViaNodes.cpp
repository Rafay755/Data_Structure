#include <iostream>
#include <vector>
#include "Queue.h"
using namespace std;
class BinaryTree;
class TreeNode
{
private:
    int data;
    TreeNode *left;
    TreeNode *right;

public:
    TreeNode() : data(0), left(nullptr), right(nullptr) {}
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
    friend class BinaryTree;
};
class BinaryTree
{
private:
    TreeNode *root;

public:
    BinaryTree() : root(nullptr) {}
    void insertIntoTree(int val, TreeNode *parent, char position)

    {
        TreeNode *nodeToInsert = new TreeNode(val);
        if (parent == nullptr && position == ' ')
        {
            if (root == nullptr)
            {
                parent = nodeToInsert;
                root = parent;
            }
            else
            {
                cout << "Root is already there.Enter child." << endl;
            }
        }
        else
        {
            if (parent != nullptr && position == 'L')
            {
                if (parent->left == nullptr)
                {
                    parent->left = nodeToInsert;
                }
                else
                {
                    cout << "Left child of that parent is already there." << endl;
                }
            }
            else if (parent != nullptr && position == 'R')
            {
                if (parent->right == nullptr)
                {
                    parent->right = nodeToInsert;
                }
                else
                {
                    cout << "Right child of that parent is already there." << endl;
                }
            }
            else
            {
                cout << "Position that you entered is incorrect." << endl;
            }
        }
    }
    void inOrderTraversal(TreeNode *r)
    {
        if (r == nullptr)
        {
            return;
        }
        inOrderTraversal(r->left);
        cout << r->data;
        inOrderTraversal(r->right);
    }
    void preOrderTraversal(TreeNode *r)
    {
        if (r == nullptr)
        {
            return;
        }
        cout << r->data;
        preOrderTraversal(r->left);
        preOrderTraversal(r->right);
    }
    void postOrderTraversal(TreeNode *r)
    {

        if (r == nullptr)
        {
            return;
        }

        postOrderTraversal(r->left);
        postOrderTraversal(r->right);
        cout << r->data;
    }
    vector<vector<int>> levelOrderTraversal(TreeNode *r)
    {
        Queue<TreeNode *> q;
        vector<vector<int>> ans;
       
        if (r == nullptr)
        {
            return ans;
        }

        q.enqueue(r);
        while (!q.isEmpty())
        {
             vector<int> level;
            int size = q.size();
            for (size_t i = 0; i < size; i++)
            {
                TreeNode *node = q.peekFront();
                q.dequeue();
                
                if (node->left != nullptr)
                {
                    q.enqueue(node->left);
                }
                if (node->right != nullptr)
                {
                    q.enqueue(node->right);
                }
                level.push_back(node->data);
            }
            ans.push_back(level);
        }
        return ans;
    }
    void displayLevelOrder()
    {
        vector<vector<int>> levelOrders = levelOrderTraversal(root);
        for (const auto &levels : levelOrders)
        {
            for (int val : levels)
            {
                cout << val << "\t";
            }
            cout << endl;
        }
    }
    TreeNode *find(int val, TreeNode *r)
    {
        if (r == nullptr)
        {
            return nullptr;
        }
        if (r->data == val)
        {
            return r;
        }
        return find(val, r->left);
        return find(val, r->right);
    }
    TreeNode *getRoot()
    {
        return root;
    }
    ~BinaryTree()
    {
        delete root;
        root = nullptr;
    }
    
};
int main()
{
    BinaryTree tree;
    int choice, value;
    TreeNode *parent = nullptr;
    char position;

    while (true)
    {
        cout << "1. Insert Node\n";
        cout << "2. Display In-Order Traversal\n";
        cout << "3. Display Pre-Order Traversal\n";
        cout << "4. Display Post-Order Traversal\n";
        cout << "5. Display Level-Order Traversal\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            cout << "Enter parent value (0 if root): ";
            int parentValue;
            cin >> parentValue;
            if (parentValue == 0)
            {
                tree.insertIntoTree(value, nullptr, ' ');
            }
            else
            {
                if (parentValue != 0)
                {
                    parent = tree.find(parentValue, tree.getRoot());
                    if (parent == nullptr)
                    {
                        cout << "Parent not found!" << endl;
                        break;
                    }
                    cout << "Enter position (L for left, R for right): ";
                    cin >> position;
                    tree.insertIntoTree(value, parent, position);
                }
            }

            break;

        case 2:
            cout << "In-Order Traversal: ";
            tree.inOrderTraversal(tree.getRoot());
            cout << endl;
            break;

        case 3:
            cout << "Pre-Order Traversal: ";
            tree.preOrderTraversal(tree.getRoot());
            cout << endl;
            break;

        case 4:
            cout << "Post-Order Traversal: ";
            tree.postOrderTraversal(tree.getRoot());
            cout << endl;
            break;

        case 5:
            cout << "Level-Order Traversal:\n";
            tree.displayLevelOrder();
            break;

        case 6:
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}
#include <iostream>
using namespace std;
#include <vector>
#include "Queue.h"

class BinarySearchTree;

class TreeNode
{
private:
    int data;
    TreeNode *right;
    TreeNode *left;

public:
    TreeNode() : right(nullptr), left(nullptr), data(0) {}
    TreeNode(int d) : right(nullptr), left(nullptr), data(d) {}
    friend class BinarySearchTree;
};

class BinarySearchTree
{
private:
    TreeNode *root;

public:
    BinarySearchTree()
    {
        root = nullptr;
    }

    TreeNode *iterativeInsertion(TreeNode *r, int val)
    {
        if (r == nullptr)
        {
            return new TreeNode(val);
        }
        else
        {
            TreeNode *current = r;
            while (true)
            {
                if (current->data > val)
                {
                    if (current->left != nullptr)
                    {
                        current = current->left;
                    }
                    else
                    {
                        current->left = new TreeNode(val);
                        break;
                    }
                }
                else
                {
                    if (current->right != nullptr)
                    {
                        current = current->right;
                    }
                    else
                    {
                        current->right = new TreeNode(val);
                        break;
                    }
                }
            }
            return r;
        }
    }

    TreeNode *recursiveInsertion(TreeNode *r, int val)
    {
        if (r == nullptr)
        {
            return new TreeNode(val);
        }
        if (r->data > val)
        {
            r->left = recursiveInsertion(r->left, val);
        }
        else
        {
            r->right = recursiveInsertion(r->right, val);
        }
        return r;
    }

    TreeNode *getSuccessor(TreeNode *r)
    {
        if (r == nullptr)
        {
            return r;
        }
        TreeNode *tracker = r->right;
        while (tracker != nullptr && tracker->left != nullptr)
        {
            tracker = tracker->left;
        }
        return tracker;
    }

    TreeNode *getPredecessor(TreeNode *r)
    {
        if (r == nullptr)
        {
            return r;
        }
        else
        {
            TreeNode *tracker = r->left;
            while (tracker != nullptr && tracker->right != nullptr)
            {
                tracker = tracker->right;
            }
            return tracker;
        }
    }

    TreeNode *deletionViaSuccessor(TreeNode *r, int val)
    {
        if (r == nullptr)
        {
            return r;
        }
        if (r->data == val)
        {
            if (r->right == nullptr && r->left == nullptr)
            {
                delete r;
                r = nullptr;
                return r;
            }
            else if (r->left == nullptr)
            {
                TreeNode *temp = r->right;
                delete r;
                r = nullptr;
                return temp;
            }
            else if (r->right == nullptr)
            {
                TreeNode *temp = r->left;
                delete r;
                r = nullptr;
                return temp;
            }
            else
            {
                TreeNode *successor = getSuccessor(r);
                r->data = successor->data;
                r->right = deletionViaSuccessor(r->right, successor->data);
                return r;
            }
        }
        else if (r->data > val)
        {
            r->left = deletionViaSuccessor(r->left, val);
        }
        else
        {
            r->right = deletionViaSuccessor(r->right, val);
        }
        return r;
    }

    TreeNode *deletionViaPredecessor(TreeNode *r, int val)
    {
        if (r == nullptr)
        {
            return r;
        }
        if (r->data == val)
        {
            if (r->right == nullptr && r->left == nullptr)
            {
                delete r;
                r = nullptr;
                return r;
            }
            else if (r->left == nullptr)
            {
                TreeNode *temp = r->right;
                delete r;
                r = nullptr;
                return temp;
            }
            else if (r->right == nullptr)
            {
                TreeNode *temp = r->left;
                delete r;
                r = nullptr;
                return temp;
            }
            else
            {
                TreeNode *predecessor = getPredecessor(r);
                r->data = predecessor->data;
                r->left = deletionViaPredecessor(r->left, predecessor->data);
                return r;
            }
        }
        else if (r->data > val)
        {
            r->left = deletionViaPredecessor(r->left, val);
        }
        else
        {
            r->right = deletionViaPredecessor(r->right, val);
        }
        return r;
    }

    void insertIterative(int d)
    {
        root = iterativeInsertion(root, d);
    }

    void insertRecursive(int d)
    {
        root = recursiveInsertion(root, d);
    }

    void inOrderTraversal(TreeNode *r)
    {
        if (r == nullptr)
        {
            return;
        }
        inOrderTraversal(r->left);
        cout << r->data << "\t";
        inOrderTraversal(r->right);
    }

    void preOrderTraversal(TreeNode *r)
    {
        if (r == nullptr)
        {
            return;
        }
        cout << r->data << "\t";
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
        cout << r->data << "\t";
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
            for (int i = 0; i < size; i++)
            {
                TreeNode *node = q.peekFront();
                q.dequeue();

                level.push_back(node->data);

                if (node->left != nullptr)
                {
                    q.enqueue(node->left);
                }
                if (node->right != nullptr)
                {
                    q.enqueue(node->right);
                }
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

    TreeNode *getRoot() const
    {
        return root;
    }

    void takeInputIterative()
    {
        int d;
        cout << "Enter -1 to stop." << endl;
        while (true)
        {
            cin >> d;
            if (d == -1)
            {
                break;
            }
            insertIterative(d);
        }
    }

    void takeInputRecursive()
    {
        int d;
        cout << "Enter -1 to stop." << endl;
        while (true)
        {
            cin >> d;
            if (d == -1)
            {
                break;
            }
            insertRecursive(d);
        }
    }
};

int main()
{
    BinarySearchTree bst;
    int choice, value;

    do
    {
        cout << "\nBinary Search Tree Menu" << endl;
        cout << "1. Insert nodes (Iterative)" << endl;
        cout << "2. Insert nodes (Recursive)" << endl;
        cout << "3. Delete node via Successor" << endl;
        cout << "4. Delete node via Predecessor" << endl;
        cout << "5. In-Order Traversal" << endl;
        cout << "6. Pre-Order Traversal" << endl;
        cout << "7. Post-Order Traversal" << endl;
        cout << "8. Level-Order Traversal" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice (1-9): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Insert nodes iteratively:" << endl;
            bst.takeInputIterative();
            break;

        case 2:
            cout << "Insert nodes recursively:" << endl;
            bst.takeInputRecursive();
            break;

        case 3:
            cout << "Enter value to delete via Successor: ";
            cin >> value;
            bst.deletionViaSuccessor(bst.getRoot(), value);
            break;

        case 4:
            cout << "Enter value to delete via Predecessor: ";
            cin >> value;
            bst.deletionViaPredecessor(bst.getRoot(), value);
            break;

        case 5:
            cout << "In-Order Traversal: ";
            bst.inOrderTraversal(bst.getRoot());
            cout << endl;
            break;

        case 6:
            cout << "Pre-Order Traversal: ";
            bst.preOrderTraversal(bst.getRoot());
            cout << endl;
            break;

        case 7:
            cout << "Post-Order Traversal: ";
            bst.postOrderTraversal(bst.getRoot());
            cout << endl;
            break;

        case 8:
            cout << "Level-Order Traversal: " << endl;
            bst.displayLevelOrder();
            break;

        case 9:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice. Please select a number between 1 and 9." << endl;
            break;
        }
    } while (choice != 9);

    return 0;
}
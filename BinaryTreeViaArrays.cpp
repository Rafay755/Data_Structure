#include <iostream>
using namespace std;

class BinaryTree
{
private:
    int *tree;
    int count;
    int size;

    void Delete(int index)
    {
        if (index >= count || tree[index] == -1)
        {
            return;
        }
        Delete(2 * index);
        Delete(2 * index + 1);
        tree[index] = -1;
    }

public:
    BinaryTree() : tree(nullptr), count(1), size(0) {}

    BinaryTree(int s) : size(s), count(1)
    {
        tree = new int[s];
        for (size_t i = 0; i < s; i++)
        {
            tree[i] = -1;
        }
    }

    void insert(int val)
    {
        if (count > size)
        {
            cout << "Tree is already full." << endl;
           
        }
       else
        {
            tree[count] = val;
            count++;
            cout << "Value entered into tree successfully." << endl;
        }
    }

    int getParent(int index)
    {
        if (index != 1 && index <= size)
        {
            return tree[index / 2];
        }
        else
        {
            cout << "Invalid index or parent does not exist." << endl;
            return -1;
        }
    }

    int getLeft(int parentIndex)
    {
        if (parentIndex <= size)
        {
            return tree[2 * parentIndex];
        }
        else
        {
            return -1;
        }
    }

    int getRight(int parentIndex)
    {
        if (parentIndex <= size)
        {
            return tree[2 * parentIndex + 1];
        }
        else
        {
            return -1;
        }
    }

    void deleteFromTree(int val)
    {
        int index = -1;
        for (size_t i = 0; i < count; i++)
        {
            if (tree[i] == val)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            cout << "Key to be deleted not found." << endl;
            return;
        }
        Delete(index);
        if (index != count - 1)
        {
            tree[index] = tree[count - 1];
            tree[count - 1] = -1;
        }
        count--;
        cout << "Value deleted from tree successfully." << endl;
    }

    void inOrderTraversal(int index)
    {
        if (index >= count || tree[index] == -1)
        {
            return;
        }
        inOrderTraversal(2 * index);
        cout << tree[index] << "\t";
        inOrderTraversal(2 * index + 1);
    }

    void displayInOrder()
    {
        cout << "In-order Traversal: ";
        inOrderTraversal(1);
        cout << endl;
    }
    void print()
    {
        for (size_t i = 0; i < count; i++)
        {
            cout<<tree[i]<<"\t";
        }

        
    }
};

int main() {
    int size;
    cout << "Enter the size of the binary tree: ";
    cin >> size;

    BinaryTree tree(size);

    int choice, value, index;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert a value\n";
        cout << "2. Delete a value\n";
        cout << "3. Display In-Order Traversal\n";
        cout << "4. Get Parent of a node\n";
        cout << "5. Get Left Child of a node\n";
        cout << "6. Get Right Child of a node\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            cout << "Enter value to delete: ";
            cin >> value;
            tree.deleteFromTree(value);
            break;
        case 3:
            tree.displayInOrder();
            break;
        case 4:
            cout << "Enter index to get parent: ";
            cin >> index;
            value = tree.getParent(index);
            if (value != -1) {
                cout << "Parent of node at index " << index << " is: " << value << endl;
            }
            break;
        case 5:
            cout << "Enter index to get left child: ";
            cin >> index;
            value = tree.getLeft(index);
            if (value != -1) {
                cout << "Left child of node at index " << index << " is: " << value << endl;
            }
            break;
        case 6:
            cout << "Enter index to get right child: ";
            cin >> index;
            value = tree.getRight(index);
            if (value != -1) {
                cout << "Right child of node at index " << index << " is: " << value << endl;
            }
            break;
        case 7:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);
    tree.print();

    return 0;
}
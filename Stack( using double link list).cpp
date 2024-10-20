#include <iostream>
using namespace std;

class stack;

class Node
{
private:
    int data;
    Node *prev;
    Node *next;

public:
    Node() : data(0), prev(nullptr), next(nullptr) {}
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
    ~Node() {}

    friend stack;
};

class stack
{
private:
    Node *top;

public:
    stack() : top(nullptr) {}

    void push(int val)
    {
        Node *newNode = new Node(val);
        if (top == nullptr)
        {
            top = newNode;
        }
        else
        {
            newNode->next = top;
            top->prev = newNode;
            top = newNode;
        }
    }

    int pop()
    {
        if (isEmpty())
        {
            return -1;
        }
        else
        {
            Node *temp = top;
            int val = temp->data;
            top = top->next;
            if (top != nullptr)
            {
                top->prev = nullptr;
            }

            delete temp;
            return val;
        }
    }

    bool isEmpty()
    {
        if (top == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void display()
    {
        Node *temp = top;
        if(top==nullptr)
        {
            cout<<"stack is empty."<<endl;
            return;
        }
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    int Top()
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return -1;
        }
        else
        {
            return top->data;
        }
    }
    int Size()
    {
        Node *temp = top;
        int count = 0;
        while (temp != nullptr)
        {
            
            temp = temp->next;
            count++;
        }
        return count;
    }
    ~stack()
    {
        while (top != nullptr)
        {
            Node *deletor = top;
            top = top->next;
            delete deletor;
        }
        top = nullptr;
    }
};

int main()
{
    stack stk;
    int  value;

   
    

    int choice;
    do
    {
        cout << "******************************************************************************************************************************" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Check if Empty" << endl;
        cout << "4. Get Top" << endl;
        cout << "5. Get Size" << endl;
        cout << "6. Display Stack" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to push: ";
            cin >> value;
            stk.push(value);
            break;

        case 2:
            value = stk.pop();
            if (value == -1)
                cout << "Stack is empty." << endl;
            else
                cout << "Popped value: " << value << endl;
            break;

        case 3:
            if (stk.isEmpty())
                cout << "Stack is empty." << endl;
            else
                cout << "Stack is not empty." << endl;
            break;

        case 4:
            value = stk.Top();
            if (value != -1)
                cout << "Top value: " << value << endl;
            break;

        case 5:
            cout << "Size of stack: " << stk.Size() << endl;
            break;

        case 6:
            cout << "Stack contents: ";
            stk.display();
            break;

        case 7:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
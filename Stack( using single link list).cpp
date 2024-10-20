#include <iostream>
using namespace std;

class Node
{
private:
    int data;
    Node *next;

public:
    Node()
    {
        data = 0;
        next = nullptr;
    }
    Node(int s)
    {
        data = s;
        next = nullptr;
    }
    ~Node()
    {
    }
    friend class stack;
};

class stack
{
    Node *top;
    Node *bottom;

public:
    stack()
    {
        top = bottom = nullptr;
    }
    bool isEmpty()
    {
        if(top==nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void push(int val)
    {
        Node *newNode = new Node(val);
        if (top == nullptr)
        {
            top = bottom = newNode;
        }
        else
        {
            newNode->next = top;
            top = newNode;
        }
    }
    int pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return -1;
        }
        else
        {
            int val = top->data;
            Node *temp = top;
            top = top->next;
            delete temp;
            return val;
        }
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
            Node *temp = bottom;
            bottom = bottom->next;
            delete temp;
        }
        top = bottom = nullptr;
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
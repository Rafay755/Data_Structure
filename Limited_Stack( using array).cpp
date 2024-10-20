#include <iostream>
using namespace std;

class Stack
{
private:
    int size;
    int top;
    int *stk;

public:
    Stack() : size(0), top(-1), stk(nullptr) {}

    Stack(int s) : size(s), top(-1)
    {
        stk = new int[s];
    }

    ~Stack()
    {
        delete[] stk;
        stk = nullptr;
    }

    void push(int val)
    {
        if (top != size - 1)
        {
            top++;
            stk[top] = val;
        }
        else
        {
            cout << "Stack is full." << endl;
        }
    }

    int pop()
    {
        if (top != -1)
        {
            int val = stk[top];
            top--;
            return val;
        }
        else
        {
            cout << "Stack is empty." << endl;
            return -1;
        }
    }

    bool isEmpty()
    {
        if (top == -1)
        {
            return true;
        }
    }

    bool isFull()
    {
        if (top == (size - 1))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    int getSize() const
    {
        return size;
    }

    void show()
    {
        cout << "Stack of size " << size << " is: " << endl;
        for (int i = top; i >= 0; i--)
        {
            cout << stk[i] << "\t";
        }
        cout << endl;
    }
    int Top()
    {
        if (top == -1)
        {
            return -1;
        }
        else
        {
            return stk[top];
        }
    }
};

int main()
{
    int size;
    cout << "Enter the size of the stack: ";
    cin >> size;
    Stack stk(size);
    int choice, value;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Check if Full\n";
        cout << "4. Check if Empty\n";
        cout << "5. Show Top Element\n";
        cout << "6. Show Stack\n";
        cout << "7. Get Stack Size\n";
        cout << "8. Exit\n";
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
            if (value != -1)
            {
                cout << "Popped value: " << value << endl;
            }
            break;
        case 3:
            if (stk.isFull())
            {
                cout << "Stack is full." << endl;
            }
            else
            {
                cout << "Stack is not full." << endl;
            }
            break;
        case 4:
            if (stk.isEmpty())
            {
                cout << "Stack is empty." << endl;
            }
            else
            {
                cout << "Stack is not empty." << endl;
            }
            break;
        case 5:
            value = stk.Top();
            if (value != -1)
            {
                cout << "Top element: " << value << endl;
            }
            else
            {
                cout << "Stack is empty." << endl;
            }
            break;
        case 6:
            stk.show();
            break;
        case 7:
            cout << "Stack size: " << stk.getSize() << endl;
            break;
        case 8:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}

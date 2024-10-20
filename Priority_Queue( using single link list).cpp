#include <iostream>
using namespace std;

class Queue_SLL2;

class Node
{
private:
    int data;
    int prior;
    Node *next;

public:
    Node()
    {
        data = 0;
        prior = 0;
        next = nullptr;
    }

    Node(int val, int pr)
    {
        data = val;
        prior = pr;
        next = nullptr;
    }

    friend Queue_SLL2;
};

class Queue_SLL2
{
private:
    Node *front;
    Node *rear;

public:
    Queue_SLL2()
    {
        front = nullptr;
        rear = nullptr;
    }

    void enqueue(int x, int p)
    {
        Node *newNode = new Node(x, p);
        if (rear == nullptr)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
            newNode->next = nullptr;
        }
    }

    int dequeue()
    {
        if (front == nullptr)
        {
            cout << "Queue is empty. Cannot dequeue.\n";
            return -1;
        }
        else if (front == rear)
        {
            Node *temp = front;
            int data = temp->data;
            delete front;
            front = rear = nullptr;
            return data;
        }
        else
        {
            Node *temp = front;
            front = front->next;
            int data = temp->data;
            delete temp;
            return data;
        }
    }

    void addFront(int val, int pr)
    {
        Node *newNode = new Node(val, pr);
        if (front == nullptr)
        {
            front = rear = newNode;
        }
        else
        {

            newNode->next = front;
            front = newNode;
        }
    }

    int removeRear()
    {
        if (front == nullptr)
        {
            return -1;
        }
        else if (front == rear)
        {
            int data = rear->data;
            delete rear;
            front = rear = nullptr;
            return data;
        }
        else
        {
            Node *tracker = front;
            while (tracker->next != rear)
            {
                tracker = tracker->next;
            }
            int data = rear->data;
            delete rear;
            rear = tracker;
            rear->next = nullptr;
            return data;
        }
    }

    int peek_front()
    {
        if (front == nullptr)
        {

            return -1;
        }
        else
        {

            return front->data;
        }
    }
    int peek_rear()
    {
        if (front == nullptr)
        {
            return -1;
        }
        else
        {
            return rear->data;
        }
    }
    int size()
    {
        int count = 0;
        Node *tracker = front;
        while (tracker != nullptr)
        {
            tracker = tracker->next;
            count++;
        }

        return count;
    }
    bool is_Empty()
    {
        if (front == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void priorityInsert(int val, int pr)
    {
        Node *newNode = new Node(val, pr);
        if (front == nullptr)
        {
            front = rear = newNode;
            return;
        }
        Node *tracker = front;
        Node *preTracker = nullptr;
        while (tracker != nullptr && tracker->prior > pr)
        {
            preTracker = tracker;
            tracker = tracker->next;
        }
        if (front == tracker)
        {
            Node *temp = new Node(val, pr);
            temp->next = front;
            front = temp;
           
        }
        else if (tracker == nullptr)
        {
            rear->next = newNode;
            rear = newNode;
            
        }
        else
        {
            preTracker->next = newNode;
            newNode->next = tracker;
             
        }
    }
    void priorityDeletion(int pr)
    {
        if (front == nullptr)
        {
            cout<<"Queue is empty."<<endl;
            return;
            
        }
        if (front->prior == pr)
        {
            Node *temp = front;
            front = temp->next;
            delete temp;
            cout<<"Deleted from queue."<<endl;
            return;
        }
        Node *tracker = front;
        Node *preTracker = nullptr;
        while (tracker != nullptr && tracker->prior != pr)
        {
            preTracker = tracker;
            tracker = tracker->next;
        }
        if (tracker == nullptr && tracker->prior == pr)
        {
            cout<<"Not found."<<endl;
            return;
        }
        if (tracker != nullptr && tracker->prior == pr)
        {
            Node *temp = tracker;
            preTracker->next = tracker->next;
            cout<<"Deleted from queue."<<endl;
            delete temp;
        }
        else if (tracker == nullptr && tracker->prior == pr)
        {
            preTracker->next = nullptr;
            delete tracker;
            rear = preTracker;
            cout<<"Deleted from queue."<<endl;
        }
    }
    ~Queue_SLL2()
    {
        while (front != nullptr)
        {
            Node *temp = front;
            front = front->next;
            delete temp;
        }
        front = rear = nullptr;
    }

    void print()
    {
        if (front == nullptr)
        {
            cout << "Queue is empty.\n";
        }
        else
        {
            cout << "Queue: ";
            Node *temp = front;
            while (temp != nullptr)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

int main()
{
    Queue_SLL2 q;
    int choice, val, priority;

    do
    {
        cout << "\n----- Queue Menu -----\n";
        cout << "1. Enqueue Element\n";
        cout << "2. Dequeue Element\n";
        cout << "3. Add Front\n";
        cout << "4. Remove Rear\n";
        cout << "5. Peek Front\n";
        cout << "6. Peek Rear\n";
        cout << "7. Get Size\n";
        cout << "8. Check if Empty\n";
        cout << "9. Display Queue\n";
        cout << "10. Priority insertion in  Queue\n";
        cout << "11. Priority deletion from  Queue\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to enqueue: ";
            cin >> val;
            cout << "Enter priority of value to enqueue: ";
            cin >> priority;
            q.enqueue(val, priority);
            cout << val << " enqueued into the queue.\n";
            break;
        case 2:
            val = q.dequeue();
            if (val != -1)
            {
                cout << val << " dequeued from the queue.\n";
            }
            break;
        case 3:
            cout << "Enter value to add to front: ";
            cin >> val;
            cout << "Enter priority of value to add: ";
            cin >> priority;
            q.addFront(val, priority);
            cout << val << " added to the front of the queue.\n";
            break;
        case 4:
            val = q.removeRear();
            if (val != -1)
            {
                cout << val << " removed from the rear of the queue.\n";
            }
            else
            {
                cout << "Queue is empty." << endl;
            }
            break;
        case 5:
            val = q.peek_front();
            if (val != -1)
            {
                cout << "Front element is: " << val << endl;
            }
            else
            {
                cout << "Queue is empty." << endl;
            }
            break;
        case 6:
            val = q.peek_rear();
            if (val != -1)
            {
                cout << "Rear element is: " << val << endl;
            }
            else
            {
                cout << "Queue is empty." << endl;
            }
            break;
        case 7:
            cout << "Queue size is: " << q.size() << endl;
            break;
        case 8:
            if (q.is_Empty())
            {
                cout << "Queue is empty.\n";
            }
            else
            {
                cout << "Queue is not empty.\n";
            }
            break;
        case 9:
            q.print();
            break;
        case 10:
            cout << "Enter value to insert: ";
            cin >> val;
            cout << "Enter priority of value to insert: ";
            cin >> priority;
            q.priorityInsert(val, priority);
            cout << val << " inserted into the queue.\n";
            break;

        case 11:

            cout << "Enter priority of value to delete: ";
            cin >> priority;
            q.priorityDeletion(priority);
           
            break;
        case 12:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 12);

    return 0;
}
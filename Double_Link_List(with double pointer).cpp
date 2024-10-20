#include <iostream>
using namespace std;

class DLL;

class Node
{
    int data;
    Node *prev;
    Node *next;

public:
    Node(int x = 0, Node *p = nullptr, Node *n = nullptr)
    {
        data = x;
        prev = p;
        next = n;
    }
    friend DLL;
};

class DLL
{
    Node *head;

public:
    DLL()
    {
        head = nullptr;
    }

    void insertAtHead(int val)
    {
        Node *newNode = new Node(val);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    void insertAtTail(int val)
    {
        Node *newNode = new Node(val);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node *tracker = head;
            while (tracker->next != nullptr)
            {

                tracker = tracker->next;
            }
            tracker->next = newNode;
            newNode->prev = tracker;
            newNode->next = nullptr;
        }
    }
    void insertBefore(int key, int val)
    {
        Node *tracker = nullptr;
        Node *preTracker = nullptr;
        Node *newNode = new Node(val);
        tracker = head;

        if (head == nullptr)
        {
            return;
        }
        if (head->data == key && head != nullptr)
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            return;
        }
        while (tracker != nullptr && tracker->data != key)
        {

            preTracker = tracker;
            tracker = tracker->next;
        }
        if (tracker->data == key)
        {
            preTracker->next = newNode;
            newNode->prev = preTracker;
            newNode->next = tracker;
            tracker->prev = newNode;
        }
    }
    void insertAfter(int key, int val)
    {
        if (head == nullptr)
        {
            return;
        }
        Node *newNode = new Node(val);
        Node *tracker = head;

        while (tracker != nullptr && tracker->data != key)
        {
            tracker = tracker->next;
        }
        if (tracker != nullptr && tracker->data == key)
        {
            newNode->next = tracker->next;
            newNode->prev = tracker;
            tracker->next = newNode;
        }
    }
    void deleteHead()
    {
        if (head == nullptr)
        {
            return;
        }
        if (head != nullptr)
        {
            Node *headTracker = head;
            head = head->next;
            head->prev = nullptr;
            delete headTracker;
        }
    }
    void deleteTail()
    {
        if (head == nullptr)
        {
            return;
        }
        if (head->next == nullptr)
        {
            Node *headTracker = head;
            delete headTracker;
            head = head->next;
        }
        Node *tracker = head;

        while (tracker->next != nullptr)
        {
            tracker = tracker->next;
        }
        tracker->prev->next = nullptr;
        delete tracker;
    }
    void deleteKthNode(int key, int occurence)
    {
        if (head == nullptr)
        {
            return;
        }

        int count = 0;
        Node *tracker = head;
        while (tracker != nullptr)
        {
            if (tracker->data == key)
            {
                count++;
                if (count == occurence)
                {
                    if (tracker->prev == nullptr)
                    {
                        Node *headTracker = head;
                        delete headTracker;
                        head = head->next;
                    }
                    else if (tracker->next != nullptr)
                    {

                        tracker->prev->next = tracker->next;
                        tracker->next->prev = tracker->prev;
                        delete tracker;
                    }
                    else
                    {
                        tracker->prev->next = nullptr;
                        delete tracker;
                    }
                }
            }
            tracker = tracker->next;
        }
    }
    void deleteAllOccurences(int key)
    {
        if (head == nullptr)
        {
            return;
        }

        while (head != nullptr && head->data == key)
        {
            Node *headTracker = head;
            head = head->next;
            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            delete headTracker;
        }

        Node *tracker = head;
        while (tracker != nullptr)
        {
            if (tracker->data == key)
            {
                Node *nodeToDel = tracker;
                if (tracker->next != nullptr)
                {
                    tracker->next->prev = tracker->prev;
                }
                if (tracker->prev != nullptr)
                {
                    tracker->prev->next = tracker->next;
                }
                tracker = tracker->next;
                delete nodeToDel;
            }
            else
            {
                tracker = tracker->next;
            }
        }
    }

    void DeleteNode(int val)
    {
        Node *tailTracker=head;
        while(tailTracker->next!=nullptr)
        {
            tailTracker=tailTracker->next;
        }
        if (head == nullptr)
        {
            return;
        }

        if (head->data == val)
        {
            Node *headToDelete = head;
            head = head->next;
            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else
            {
                tailTracker = nullptr;
            }
            delete headToDelete;
            return;
        }

        Node *tracker = head;
        while (tracker != nullptr && tracker->data != val)
        {
            tracker = tracker->next;
        }

        if (tracker != nullptr && tracker->data == val)
        {

            if (tracker->next != nullptr)
            {
                tracker->prev->next = tracker->next;
                tracker->next->prev = tracker->prev;
            }
            else
            {

                tailTracker = tailTracker->prev;
                if (tailTracker != nullptr)
                {
                    tailTracker->next = nullptr;
                }
                else
                {
                    head = nullptr;
                }
            }
            delete tracker;
        }
    }

    void show()
    {
        Node *headTracker = head;

        if (head == nullptr)
        {
            return;
        }

        while (headTracker != nullptr)
        {
            cout << headTracker->data << "\t";
            headTracker = headTracker->next;
        }
        cout << endl;
    }
    void showReverse()
    {
        if (head == nullptr)
        {
            return;
        }

        Node *tracker = head;
        while (tracker->next != nullptr)
        {
            tracker = tracker->next;
        }
        while (tracker != nullptr)
        {
            cout << tracker->data << "\t";
            tracker = tracker->prev;
        }
        cout << endl;
    }
    void reverse()
    {
        if (head == nullptr || head->next == nullptr)
        {
            return;
        }

        Node *temp = nullptr;
        Node *tracker = head;

        while (tracker != nullptr)
        {
            temp = tracker->prev;
            tracker->prev = tracker->next;
            tracker->next = temp;
            tracker = tracker->prev;
        }
        Node *tail = head;
        // while (tail->next != nullptr)
        // {
        //     tail = tail->next;
        // }
        if (temp != nullptr)
        {
            tail = head;
            head = temp->prev;
        }
    }
    ~DLL()
    {
        Node *deletor = head;
        while (deletor != nullptr)
        {
            Node *next = deletor->next;
            deletor = deletor->next;

            delete deletor;
            deletor = next;
        }
        head = nullptr;
    }
};

int main()
{
    DLL DoubleLinkList;
    cout << "***************************************Double Link List with Single Pointer Approach*************************************" << endl;
    DoubleLinkList.insertAtHead(5);
    DoubleLinkList.insertAtHead(4);
    DoubleLinkList.insertAtHead(3);
    DoubleLinkList.insertAtHead(2);
    DoubleLinkList.insertAtHead(1);
    DoubleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;
    cout << "Reversion of node: " << endl;
    
    cout << "Before reversion: " << endl;
    DoubleLinkList.show();
    DoubleLinkList.reverse();
    cout << "After reversion: " << endl;
    DoubleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;
    cout << "Printing Reversely: " << endl;
    
    cout << "Simple Show " << endl;
    DoubleLinkList.show();
    DoubleLinkList.reverse();
    cout << "Reversal Node: " << endl;
    DoubleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;
    cout << "Insert At Head: " << endl;
    DoubleLinkList.insertAtHead(0);
    DoubleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;
    cout << "Insert At Tail: " << endl;
    DoubleLinkList.insertAtTail(6);
    DoubleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;
    cout << "Insert 3 before 4: " << endl;
    DoubleLinkList.insertBefore(4, 3);
    DoubleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;
    cout << "Insert 3 after 5: " << endl;
    DoubleLinkList.insertAfter(3, 5);
    DoubleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;
    cout << "Delete Head: " << endl;
    DoubleLinkList.deleteHead();
    DoubleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;
    cout << "Delete Tail: " << endl;
    DoubleLinkList.deleteTail();
    DoubleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;
    cout << "Delete 3: " << endl;
    DoubleLinkList.insertAtHead(3);
    cout << "Before deletion: " << endl;
    DoubleLinkList.show();
    DoubleLinkList.DeleteNode(3);
    cout << "After deletion: " << endl;
    DoubleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;
    cout << "Delete 2nd occurence of 3: " << endl;
    DoubleLinkList.insertAtHead(3);
    cout << "Before deletion: " << endl;
    DoubleLinkList.show();
    DoubleLinkList.deleteKthNode(3, 2);
    cout << "After deletion: " << endl;
    DoubleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;

    cout << "Delete All occurence of 2: " << endl;
    DoubleLinkList.insertAtHead(2);
     DoubleLinkList.insertAtHead(2);
    cout << "Before deletion: " << endl;
    DoubleLinkList.show();
    DoubleLinkList.deleteAllOccurences(2);
    cout << "After deletion: " << endl;
    DoubleLinkList.show();
    
    cout << "****************************************************************************************************************************" << endl;
    return 0;
}
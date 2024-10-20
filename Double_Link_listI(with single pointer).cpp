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
    Node *tail;

public:
    DLL()
    {
        head = tail = nullptr;
    }

    void insertAtHead(int val)
    {
        Node *newNode = new Node(val);
        if (head == nullptr)
        {
            head = tail = newNode;
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
        Node *tailTracker = tail;
        if (head == nullptr)
        {
            head = tail = newNode;
        }

        else
        {
            tailTracker->next = newNode;
            newNode->prev = tailTracker;
            newNode->next = nullptr;
            tail = newNode;
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
        if (head == tail) 
        {
            delete head;
            head = tail = nullptr;
            return;
        }

        
        Node *tailToRemove = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete tailToRemove;
    }

    void DeleteNode(int val)
    {
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
                tail = nullptr;
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

                tail = tail->prev;
                if (tail != nullptr)
                {
                    tail->next = nullptr;
                }
                else
                {
                    head = nullptr;
                }
            }
            delete tracker;
        }
    }

    void DeleteAllOccurences(int val)
    {
        Node *tracker = head;
        Node *nextNode;

        while (tracker != nullptr)
        {
            nextNode = tracker->next;

            if (tracker->data == val)
            {
                if (tracker == head && tracker == tail)
                {
                    head = tail = nullptr;
                }
                else if (tracker == head)
                {
                    head = head->next;
                    head->prev = nullptr;
                }
                else if (tracker == tail)
                {
                    tail = tail->prev;
                    tail->next = nullptr;
                }
                else
                {
                    tracker->prev->next = tracker->next;
                    tracker->next->prev = tracker->prev;
                }
                delete tracker;
            }

            tracker = nextNode;
        }
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

        
        if (temp != nullptr)
        {
            
            tail = head;
            head = temp->prev;
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
    void nodeDeletion()
    {
        Node *deletor = head;
        while (deletor != nullptr)
        {
            Node *next = deletor->next;
            deletor = deletor->next;

            delete deletor;
            deletor = next;
        }
        head = tail = nullptr;
    }
    void deleteKth(int val, int occurrence)
    {
        if (head == nullptr) 
        {
            return;
        }

        Node *tracker = head;
        int count = 0;

        while (tracker != nullptr)
        {
            if (tracker->data == val)
            {
                count++;
                if (count == occurrence)
                {
                    if (tracker == head) 
                    {
                        head = head->next;
                        if (head != nullptr)
                        {
                            head->prev = nullptr;
                        }
                        else
                        {
                            tail = nullptr; 
                        }
                    }
                    else if (tracker == tail) 
                    {
                        tail = tail->prev;
                        if (tail != nullptr)
                        {
                            tail->next = nullptr;
                        }
                        else
                        {
                            head = nullptr; 
                        }
                    }
                    else 
                    {
                        tracker->prev->next = tracker->next;
                        tracker->next->prev = tracker->prev;
                    }

                    delete tracker;
                    return;
                }
            }
            tracker = tracker->next;
        }
    }
    void showReverse()
    {
        Node *tailTracker = tail;
        while (tailTracker != nullptr)
        {
            cout << tailTracker->data << "\t";
            tailTracker = tailTracker->prev;
        }
        cout << endl;
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
        head = tail = nullptr;
    }
};

int main()
{
    DLL DoubleLinkList;
    cout << "***************************************Double Link List with Double Pointer Approach*************************************" << endl;
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
    DoubleLinkList.deleteKth(3, 2);
    cout << "After deletion: " << endl;
    DoubleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;

    cout << "Delete All occurence of 2: " << endl;
    DoubleLinkList.insertAtHead(2);
     DoubleLinkList.insertAtHead(2);
    cout << "Before deletion: " << endl;
    DoubleLinkList.show();
    DoubleLinkList.DeleteAllOccurences(2);
    cout << "After deletion: " << endl;
    DoubleLinkList.show();
    
    cout << "****************************************************************************************************************************" << endl;
    return 0;
}
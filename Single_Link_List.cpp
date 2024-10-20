#include <iostream>
using namespace std;

class SLL;
class node
{
    int data;
    node *next;

public:
    node() : data(0), next(NULL) {}
    node(int val) : data(val), next(NULL) {}
    friend SLL;
};
class SLL
{
private:
    node *head;

public:
    SLL() : head(nullptr) {}

    void insertAtStart(int x)
    {
        node *temp = new node(x);
        temp->next = head;
        head = temp;
    }
    void insertAtTail(int x)
    {
        node *newNode = new node(x);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode = temp;
        }
    }
    void insertBefore(int key, int val)
    {
        node *temp = new node(val);
        node *tracker = head;
        node *preTracker = nullptr;
        if (head == nullptr)
        {
            return;
        }
        if (head->data == key)
        {
            temp->next = head;
            head = temp;
        }
        else
        {
            while (tracker != nullptr && tracker->data != key)
            {
                preTracker = tracker;
                tracker = tracker->next;
            }
            if (tracker != nullptr && tracker->data == key)
            {
                temp->next = tracker;
                preTracker->next = temp;
            }
        }
    }

    void insertAfter(int key, int val)
    {
        if (head == nullptr)
        {
            return;
        }

        node *tracker = head;

        while (tracker != nullptr && tracker->data != key)
        {
            tracker = tracker->next;
        }

        if (tracker != nullptr)
        {
            node *temp = new node(val);
            temp->next = tracker->next;
            tracker->next = temp;
        }
    }
    void deleteHead()
    {

        if (head == nullptr)
        {
            return;
        }
        else
        {
            node *tracker = head;
            head = head->next;
            delete tracker;
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
            delete head;
            head = nullptr;
            return;
        }

        node *tracker = head;
        node *preTracker = nullptr;
        while (tracker->next != nullptr)
        {
            preTracker = tracker;
            tracker = tracker->next;
        }
        if (tracker->next == nullptr)
        {
            preTracker->next = nullptr;
            delete tracker;
            tracker = nullptr;
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
            node *temp = head;
            head = head->next;
            delete temp;
        }

        node *tracker = head;
        while (tracker != nullptr && tracker->next != nullptr)
        {
            if (tracker->next->data == key)
            {
                node *temp = tracker->next;
                tracker->next = tracker->next->next;
                delete temp;
            }
            else
            {
                tracker = tracker->next;
            }
        }
    }

    void deleteOne(int key)
    {
        int count = 0;
        if (head == nullptr)
        {
            return;
        }

        if (head->data == key && count == 0)
        {
            node *temp = head;
            head = head->next;
            delete temp;
            count++;
        }

        node *tracker = head;
        node *preTracker = nullptr;
        while (tracker != nullptr && tracker->data != key)
        {
            preTracker = tracker;
            tracker = tracker->next;
        }

        if (tracker != nullptr && tracker->data == key && count == 0)
        {
            preTracker->next = tracker->next;
            delete tracker;
            tracker = nullptr;
        }
    }

    void show()
    {
        node *temp = head;
        if (head == nullptr)
        {
            return;
        }
        else
        {
            while (temp != nullptr)
            {
                cout << temp->data << "\t";
                temp = temp->next;
            }
            cout << endl;
        }
    }
    void deleteAllNode()
    {
        node *tracker = head;
        if (head == nullptr)
        {
            return;
        }
        while (tracker != nullptr)
        {
            node *Next = tracker->next;
            delete tracker;
            tracker = Next;
        }
        head = nullptr;
    }
    void deleteKth(int key, int occurrence)
    {
        if (head == nullptr)
        {
            return;
        }

        int count = 0;
        node *tracker = head;
        node *preTracker = nullptr;

        while (tracker != nullptr && tracker->data == key && count < occurrence)
        {
            count++;
            if (count == occurrence)
            {
                node *temp = head;
                head = head->next;
                delete temp;
                return;
            }
            preTracker = tracker;
            tracker = tracker->next;
        }

        while (tracker != nullptr)
        {
            if (tracker->data == key)
            {
                count++;
                if (count == occurrence)
                {
                    if (preTracker != nullptr)
                    {
                        preTracker->next = tracker->next;
                    }
                    delete tracker;
                    return;
                }
            }
            preTracker = tracker;
            tracker = tracker->next;
        }
    }
    void reverseSLL()
    {
        node *prev = NULL;
        node *tracker = head;
        node *next = NULL;

        while (tracker != NULL)
        {
            next = tracker->next;
            tracker->next = prev;
            prev = tracker;
            tracker = next;
        }
        head = prev;
    }
    ~SLL()
    {
        node *tracker = head;
        while (tracker != nullptr)
        {
            node *Next = tracker->next;
            delete tracker;
            tracker = Next;
            tracker = tracker->next;
        }
        head = nullptr;
    }
};

int main()
{
    SLL SingleLinkList;

    SingleLinkList.insertAtStart(6);
    SingleLinkList.insertAtStart(5);
    SingleLinkList.insertAtStart(4);
    SingleLinkList.insertAtStart(3);
    SingleLinkList.insertAtStart(2);
    SingleLinkList.insertAtStart(1);

    cout << "****************************************Single Link List with Single Pointer Approach************************************" << endl;
    SingleLinkList.show();
    cout << "**************************************************************************************************************************" << endl;
    cout << "Insert At Head(0):  " << endl;
    SingleLinkList.insertAtStart(0);
    SingleLinkList.show();
    cout << "**************************************************************************************************************************" << endl;
    cout << "Insert At Tail(7):  " << endl;
    SingleLinkList.insertAtTail(7);
    SingleLinkList.show();
    cout << "**************************************************************************************************************************" << endl;
    cout << "Insert 9 after 3:  " << endl;
    SingleLinkList.insertAfter(3, 9);
    SingleLinkList.show();
    cout << "**************************************************************************************************************************" << endl;
    cout << "Insert 4 before 1:  " << endl;
    SingleLinkList.insertBefore(1, 4);
    SingleLinkList.show();
    cout << "**************************************************************************************************************************" << endl;
    cout << "Delete Head:  " << endl;
    SingleLinkList.deleteHead();
    SingleLinkList.show();

    cout << "**************************************************************************************************************************" << endl;
    cout << "Delete Tail:  " << endl;
    SingleLinkList.deleteTail();
   
    SingleLinkList.show();
    cout << "**************************************************************************************************************************" << endl;
    cout << "Delete 3: " << endl;
    SingleLinkList.insertAtStart(3);
    cout << "Before deletion: " << endl;
    SingleLinkList.show();
    SingleLinkList.deleteOne(3);
    cout << "After deletion: " << endl;
    SingleLinkList.show();
    cout << "****************************************************************************************************************************" << endl;
    cout << "Delete 2nd occurence of 3:  " << endl;
    SingleLinkList.insertAtStart(3);
    cout << "before deletion:" << endl;
    SingleLinkList.show();
    SingleLinkList.deleteKth(3, 2);
    cout << "After deletion: " << endl;
    SingleLinkList.show();
    cout << "**************************************************************************************************************************" << endl;
    cout << "Delete All occurence of 3:  " << endl;
    SingleLinkList.insertAtStart(3);
    cout << "before deletion:" << endl;
    SingleLinkList.show();
    SingleLinkList.deleteAllOccurences(3);
    cout << "After deletion: " << endl;
    SingleLinkList.show();
    cout << "**************************************************************************************************************************" << endl;
    cout << "Reversed Node:  " << endl;
    SingleLinkList.insertAtStart(9);
    cout << "before reversion:" << endl;
    SingleLinkList.show();
    cout << "After reversion: " << endl;
    SingleLinkList.reverseSLL();
    SingleLinkList.show();
    cout << "**************************************************************************************************************************" << endl;
    cout << "Show Reversed Node:  " << endl;
    SingleLinkList.insertAtStart(8);
    cout << "Simple show:" << endl;
    SingleLinkList.show();
    cout << "revers show: " << endl;
    SingleLinkList.reverseSLL();
    SingleLinkList.show();

    return 0;
}

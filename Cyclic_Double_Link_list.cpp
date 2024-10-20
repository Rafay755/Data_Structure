#include <iostream>
using namespace std;
class CDLL;

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
    friend CDLL;
};
class CDLL
{
private:
    Node *head;
    Node *tail;

public:
    CDLL() : head(nullptr), tail(nullptr)
    {
    }
    CDLL(Node *h, Node *t) : head(h), tail(t)
    {
    }
    void insertHead(int val)
    {
        Node *newNode = new Node(val);
        if (head == nullptr)
        {
            head = tail = newNode;
            head->prev = tail;
            tail->next = head;
        }
        else
        {

            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            head->prev = tail;
            tail->next = head;
        }
    }
    void ascendingSortedInsertion(int val)
    {
        Node *newNode = new Node(val);

        if (head == nullptr)
        {
            head = tail = newNode;
            head->prev = newNode;
            tail->next = newNode;
            return;
        }

        Node *tracker = head;
        Node *preTracker = nullptr;

        do
        {
            if (val < tracker->data)
                break;

            preTracker = tracker;
            tracker = tracker->next;
        } while (tracker != head);

        if (tracker == head && val < head->data)
        {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            head = newNode;
            return;
        }

        if (tracker == head && val >= tail->data)
        {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            tail = newNode;
            return;
        }

        if (tracker != head && preTracker != nullptr)
        {
            preTracker->next = newNode;
            newNode->prev = preTracker;
            newNode->next = tracker;
            tracker->prev = newNode;
        }
    }

    void descendingSortedInsertion(int val)
    {
        Node *newNode = new Node(val);

        if (head == nullptr)
        {
            head = tail = newNode;
            head->prev = newNode;
            tail->next = newNode;
            return;
        }

        Node *tracker = head;
        Node *preTracker = nullptr;

        do
        {
            if (val > tracker->data)
                break;

            preTracker = tracker;
            tracker = tracker->next;
        } while (tracker != head);

        if (tracker == head && val > head->data)
        {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            head = newNode;
            return;
        }

        if (tracker == head && val <= tail->data)
        {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            tail = newNode;
            return;
        }

        if (tracker != head && preTracker != nullptr)
        {
            preTracker->next = newNode;
            newNode->prev = preTracker;
            newNode->next = tracker;
            tracker->prev = newNode;
        }
    }
    void insertAtTail(int val)
    {
        Node *newNode = new Node(val);
        if (head == nullptr)
        {
            head = tail = newNode;
            head->prev = newNode;
            tail->next = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        tail = newNode;
    }
    void insertBefore(int key, int val)
    {
        Node *newNode = new Node(val);
        if (head == nullptr)
        {
            return;
        }
        if (head->data == key)
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            head->prev = tail;
            tail->next = head;
            return;
        }
        Node *temp = head->next;
        while (temp != head && temp->data != key)
        {
            temp = temp->next;
        }

        if (temp->data == key)
        {
            temp->prev->next = newNode;
            newNode->prev = temp->prev;
            newNode->next = temp;
            temp->prev = newNode;
        }
    }
    void insertAfter(int key, int val)
    {
        Node *newNode = new Node(val);
        if (head == nullptr)
        {
            return;
        }
        if (head != nullptr && head->data == key)
        {
            newNode->next = head->next;
            head->next->prev = newNode;
            head->next = newNode;
            newNode->prev = head;

            return;
        }
        Node *tracker = head->next;
        while (tracker != nullptr && tracker->data != key)
        {
            tracker = tracker->next;
        }
        if (tracker->next != head)
        {
            newNode->next = tracker->next;
            tracker->next->prev = newNode;
            tracker->next = newNode;
            newNode->prev = tracker;
        }
        else if (tracker->next == head && tracker->data == key)
        {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            tail = newNode;
        }
    }
    void deleteHead()
    {
        if (head == nullptr)
        {
            return;
        }
        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }
        else if (head != nullptr)
        {
            Node *temp = head;
            head->next->prev = tail;
            head = head->next;
            tail->next = head;
            delete temp;
        }
    }
    void deleteTail()
    {
        if (head == nullptr)
        {
            return;
        }
        if (tail == head)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            Node *temp = tail;
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
            delete temp;
        }
    }
    void deleteFirstOccurence(int key)
    {
        if (head == nullptr)
        {
            return;
        }
        if (head->data == key)
        {
            Node *temp = head;
            head->next->prev = tail;
            head = head->next;
            tail->next = head;
            delete temp;
            return;
        }
        Node *tracker = head->next;
        while (tracker != head && tracker->data != key)
        {
            tracker = tracker->next;
        }
        if (tracker->data == key && tracker->next == head)
        {
            Node *temp = tracker;
            tail->prev->next = head;
            head->prev = tail;
            delete temp;
            return;
        }
        if (tracker->data == key && tracker->next != head)
        {
            Node *temp = tracker;
            tracker->prev->next = tracker->next;
            tracker->next->prev = tracker->prev;
            delete tracker;
            return;
        }
    }
    void deleteAllOccurences(int key)
    {
        if (head == nullptr)
            return;

        while (head != nullptr && head->data == key)
        {
            if (head == tail)
            {
                delete head;
                head = tail = nullptr;
                return;
            }
            Node *temp = head;
            head = head->next;
            tail->next = head;
            head->prev = tail;
            delete temp;
        }

        if (head == nullptr)
            return;

        Node *tracker = head->next;
        while (tracker != head)
        {
            if (tracker->data == key && tracker->next != head)
            {
                Node *temp = tracker;
                tracker->prev->next = tracker->next;
                tracker->next->prev = tracker->prev;
                tracker = tracker->next;
                delete temp;
            }
            else if (tracker->data == key && tracker->next == head)
            {

                Node *temp = tail;
                tail = tail->prev;
                tail->next = head;
                head->prev = tail;
                delete temp;
            }
            else
            {
                tracker = tracker->next;
            }
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

        do
        {
            temp = tracker->prev;
            tracker->prev = tracker->next;
            tracker->next = temp;
            tracker = tracker->prev;
        } while (tracker != head);

        if (temp != nullptr)
        {

            tail = head;
            head = temp->prev;
        }
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
                            head->prev = tail;
                            tail->next = head;
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
                            tail->next = head;
                            head->prev = tail;
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
    void reverseShow()
    {
        if (head == nullptr)
        {
            return;
        }
        Node *temp = tail;
        do
        {
            cout << temp->data << "\t";
            temp = temp->prev;
        } while (temp != tail);
        cout << endl;
    }
    void show()
    {
        if (head == nullptr)
        {
            return;
        }
        Node *temp = head->next;
        cout << head->data << "\t";
        while (temp != head)
        {
            cout << temp->data << "\t";
            temp = temp->next;
        }
        cout << endl;
    }
    ~CDLL()
    {
        Node *deletor = head;
        do
        {
            Node *next = deletor->next;
            deletor = deletor->next;

            delete deletor;
            deletor = next;
        } while (deletor != head);

        head = tail = nullptr;
    }
};
int main()
{
    CDLL DoubleLinkList;
    int choice, val, key;

    while (true)
    {
        cout << "********************* Circular Doubly Linked List Menu *********************" << endl;
        cout << "1. Insert at Head" << endl;
        cout << "2. Insert at Tail" << endl;
        cout << "3. Insert before a value" << endl;
        cout << "4. Insert after a value" << endl;
        cout << "5. Ascending Sorted Insertion" << endl;
        cout << "6. Descending Sorted Insertion" << endl;
        cout << "7. Delete Head" << endl;
        cout << "8. Delete Tail" << endl;
        cout << "9. Delete First Occurrence of a value" << endl;
        cout << "10. Delete All Occurrences of a value" << endl;
        cout << "11. Delete Kth Occurrence of a value" << endl;
        cout << "12. Reverse the list" << endl;
        cout << "13. Show list" << endl;
        cout << "14. Show list in reverse order" << endl;
        cout << "15. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert at head: ";
            cin >> val;
            DoubleLinkList.insertHead(val);
            break;
        case 2:
            cout << "Enter value to insert at tail: ";
            cin >> val;
            DoubleLinkList.insertAtTail(val);
            break;
        case 3:
            cout << "Enter key value to insert before: ";
            cin >> key;
            cout << "Enter value to insert: ";
            cin >> val;
            DoubleLinkList.insertBefore(key, val);
            break;
        case 4:
            cout << "Enter key value to insert after: ";
            cin >> key;
            cout << "Enter value to insert: ";
            cin >> val;
            DoubleLinkList.insertAfter(key, val);
            break;
        case 5:
            cout << "Enter value for ascending sorted insertion: ";
            cin >> val;
            DoubleLinkList.ascendingSortedInsertion(val);
            break;
        case 6:
            cout << "Enter value for descending sorted insertion: ";
            cin >> val;
            DoubleLinkList.descendingSortedInsertion(val);
            break;
        case 7:
            DoubleLinkList.deleteHead();
            break;
        case 8:
            DoubleLinkList.deleteTail();
            break;
        case 9:
            cout << "Enter value to delete first occurrence: ";
            cin >> val;
            DoubleLinkList.deleteFirstOccurence(val);
            break;
        case 10:
            cout << "Enter value to delete all occurrences: ";
            cin >> val;
            DoubleLinkList.deleteAllOccurences(val);
            break;
        case 11:
            int occurrence;
            cout << "Enter value to delete: ";
            cin >> val;
            cout << "Enter occurrence to delete: ";
            cin >> occurrence;
            DoubleLinkList.deleteKth(val, occurrence);
            break;
        case 12:
            DoubleLinkList.reverse();
            break;
        case 13:
            DoubleLinkList.show();
            break;
        case 14:
            DoubleLinkList.reverseShow();
            break;
        case 15:
            cout << "Exiting program..." << endl;
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
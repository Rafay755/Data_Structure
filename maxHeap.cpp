#include <iostream>
using namespace std;

class Heap
{
private:
    int *maxHeap;
    int size;
    int count;

    void heapify(int index, int s)
    {
        int left = 2 * index;
        int right = 2 * index + 1;
        int largest = index;

        if (left <= s && maxHeap[left] > maxHeap[largest])
        {
            largest = left;
        }
        if (right <= s && maxHeap[right] > maxHeap[largest])
        {
            largest = right;
        }
        if (largest != index)
        {
            swap(maxHeap[index], maxHeap[largest]);
            heapify(largest, s);
        }
    }

public:
     Heap(int s) : size(s), count(1) // Initial count is 1 to handle one-based indexing
    {
        maxHeap = new int[s + 1];
    }

    ~Heap()
    {
        delete[] maxHeap;
    }

    void insert(int val)
    {
        if (count > size)
        {
            cout << "Heap is full." << endl;
            return;
        }

        maxHeap[count] = val;
        count++;
    }

    void buildHeap()
    {
        for (int i = count / 2; i >= 1; i--)
        {
            heapify(i, count);
        }
    }

    void heapSort()
    {
        buildHeap();
        for (int i = count-1; i >= 1; i--)
        {
            swap(maxHeap[1], maxHeap[i]);
            heapify(1, i - 1);
        }
    }
    void printHeap() const
    {
        for (int i = 1; i < count; i++)
        {
            cout << maxHeap[i] << "\t";
        }
        cout << endl;
    }
    void deleteFromHeap()
    {

        if (count <= 1)
        {
            cout << "Heap is empty." << endl;
            return;
        }
        maxHeap[1] = maxHeap[count - 1];
        count--;
        int i = 1;
        while (2 * i < count)
        {
            if (maxHeap[2 * i] > maxHeap[2 * i + 1])
            {
                swap(maxHeap[2 * i], maxHeap[i]);
                i = 2 * i;
            }
            else
            {
                swap(maxHeap[2 * i + 1], maxHeap[i]);
                i = 2 * i + 1;
            }
        }
    }
};

int main()
{
    int size;
    cout << "Enter size of heap: ";
    cin >> size;

    Heap heap(size);

    int choice, value;
    do
    {
        cout << "\nHeap Operations Menu" << endl;
        cout << "1. Insert into heap" << endl;
        cout << "2. Build heap" << endl;
        cout << "3. Delete from heap" << endl;
        cout << "4. Heap sort" << endl;
        cout << "5. Print heap" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            heap.insert(value);
            break;

        case 2:
            heap.buildHeap();
            cout << "Heap built successfully." << endl;
            break;

        case 3:
            heap.deleteFromHeap();
            cout << "Root deleted from heap." << endl;
            break;

        case 4:
            heap.heapSort();
            cout << "Heap sorted." << endl;
            break;

        case 5:
            cout << "Heap contents: ";
            heap.printHeap();
            break;

        case 6:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice. Please select a number between 1 and 6." << endl;
            break;
        }
    } while (choice != 6);

    return 0;
}
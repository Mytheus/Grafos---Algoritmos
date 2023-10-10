#include <iostream>
#include <bits/stdc++.h>

using namespace std;


class PQueue
{
    // Número de elementos dentro da heap
private:
    int heapSize = 0;

    // Lista para os elementos na heap
    vector<int> heap;

    int less(int i, int j)
    {
        return heap.at(i)<=heap.at(j);
    }
    //UP
    void swim(int k)
    {
        int parent = (k-1) / 2;

        while (k>0 && less(k, parent))
        {
            this->swap(parent, k);
            k = parent;

            parent = (k-1)/2;
        }
    }
    //DOWN
    void sink(int k)
    {
        while (1)
        {
            int left = 2 * k + 1;
            int right = 2 * k + 2;
            int smallest = left;
            
            if (right < heapSize && less(right, left)) smallest = right;

            if (left >= heapSize || less(k, smallest)) break;

            this->swap(smallest, k);
            k = smallest;
        }
    }

    void swap(int i, int j)
    {
        int aux = heap[j];
        heap[j] = heap[i];
        heap[i] = aux;
    }
    int removeAt(int i)
    {
        if (isEmpty()) return -1;
        heapSize--;
        int removido = heap[i];
        this->swap(i, heapSize);
        heap.pop_back();

        if (i == heapSize) return removido;

        int elem = heap[i];

        sink(i);

        if (heap[i]==elem) swim(i);

        return removido;

    }
public:
    int isEmpty()
    {
        return heapSize == 0;
    }


    int size(){
        return heapSize;
    }

    int peek(){
        if (isEmpty()) return -1;
        return heap.at(0);
    }

    int poll()
    {
        return removeAt(0);
    }

    //Linear
    int contains(int elem)
    {
        for (int i = 0; i < heapSize; i++)
        {
            if (heap.at(i)==elem) return 1;
        }
        return 0;
    }

    void add(int elem)
    {
        heap.push_back(elem);
        swim(heapSize);
        heapSize++;
    }



    int remove (int elem)
    {
        for (int i = 0; i < heapSize; i++)
        {
            if (elem == heap[i])
            {
                removeAt(i);
                return 1;
            }
        }
        return 0;
    }


    int isMinHeap(int k)
    {
        if (k >= heapSize) return true;

        int left = 2 * k+1;
        int right = 2 * k+2;

        if (left < heapSize && !less(k, left)) return false;
        if (right < heapSize && !less(k, right)) return false;

        return isMinHeap(left) && isMinHeap(right);
    }

};

int main()
{
    PQueue filaP;
    filaP.add(14);
    filaP.add(4);
    filaP.add(8);
    filaP.add(1);
    filaP.add(3);
    filaP.add(22);
    cout << filaP.poll() << endl;
    filaP.add(2);
    cout << filaP.poll() << endl;
    filaP.add(4);
    cout << filaP.poll() << endl;
    filaP.add(5);
    filaP.add(9);
    while (!filaP.isEmpty())
    {
        cout << filaP.poll() << endl;
    }
    
    return 0;

}
#include <iostream>

using namespace std;

template<class T>
class MinPQ {
public:
	virtual ~MinPQ(){}
	virtual bool IsEmpty() = 0;
	virtual const T&Top() const = 0;
	virtual void Push(const T&) = 0;
	virtual void Pop() = 0;
};

template<class T>
class MinHeap :public MinPQ<T> {
public:
	MinHeap(int theCapacity = 10)
	{
		if (theCapacity < 1) throw "Capacity must be >=1.";
		capacity = theCapacity;
		heapsize = 0;
		heap = new T[capacity + 1];
	}
	void DoubleSize()
	{
		T * temp = new T[capacity + 1];
		for (int i = 0; i <= capacity; i++)
			temp[i] = heap[i];
		delete heap;
		heap = new T[capacity * 2 + 1];
		for (int i = 0; i <= capacity; i++)
			heap[i] = temp[i];
		capacity *= 2;
		delete temp;
	}
	void Push(const T& e)
	{
		if (heapsize == capacity)
		{
			DoubleSize();
		}
		int currentNode = ++heapsize;
		while (currentNode != 1 && heap[currentNode / 2] > e)
		{
			heap[currentNode] = heap[currentNode / 2];
			currentNode /= 2;
		}
		heap[currentNode] = e;
	}
	void Pop()
	{
		if (IsEmpty()) throw "Heap is empty. Cannot delete.";
		heap[1].~T();

		T lastE = heap[heapsize--];
		int currentNode = 1;
		int child = 2;
		while (child <= heapsize)
		{
			if (child<heapsize&&heap[child]>heap[child + 1]) child++;

			if (lastE <= heap[child]) break;

			heap[currentNode] = heap[child];
			currentNode = child;
			child *= 2;
		}
		heap[currentNode] = lastE;
	}
	const T& Top() const
	{
		return heap[1];
	}
	bool IsEmpty()
	{
		if (heapsize >= 1)
			return false;
		return true;
	}
private:
	T * heap;
	int heapsize;
	int capacity;

};

int main()
{
	MinHeap<int> myMinHeap(10);
	for (int i = 0; i < 10; i++)
	{
		const int temp = i;
		myMinHeap.Push(temp);
	}
	while (!myMinHeap.IsEmpty())
	{
		cout << myMinHeap.Top() << "  ";
		myMinHeap.Pop();
	}
	system("pause");
	return 0;
}
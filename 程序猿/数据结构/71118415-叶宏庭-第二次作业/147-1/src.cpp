#include <iostream>

using namespace std;

enum Operation{myPush,myPop};//自定义枚举类型供lastOp使用。

template<class T>
class Queue {
public:
	Queue(int c)
	{
		capacity = c;
		queue = new T[c];
		front = capacity-1;
		rear = -1;
		lastOp = myPush;
	}
	void Push(T a)
	{
		if (front == (rear + 1) % capacity)//在队列只剩一个空间时，加倍队列空间
			DoublingQueue();
		rear = (rear + 1) % capacity;//队尾后移一位
		queue[rear] = a;//加入新来的值
		lastOp = myPush;//将lastOp的值改为Push.
	}
	void DoublingQueue()
	{
		T *newQueue = new T[capacity * 2];

		int start = (front + 1) % capacity;//若front目前指向队尾或者队伍第一个，则只需要拷贝一次。
		if (start < 2)
			copy(queue + start, queue + start + capacity - 1, newQueue);
		else
		{
			copy(queue + start, queue + capacity, newQueue);//先拷贝front到物理空间队尾的数据
			copy(queue, queue + rear + 1, newQueue + capacity - start);//再拷贝物理空间开始到队尾的数据
		}
		front = 2 * capacity - 1;//拷贝完，队头指向最后一个空间
		rear = capacity - 2;//加倍空间前，队列共有capacity-1个元素，所以拷贝后，队尾元素的下标为capacity-2
		capacity *= 2;
		delete[]queue;
		queue = newQueue;
	}
	void Pop()
	{
		if (isEmpty())
			cout << "It's a empty queue, can't pop." << endl;
		else
		{
			front = (front + 1) % capacity;
			queue[front].~T();
			lastOp = myPop;//将lastOp的值改为Pop
		}
	}
	void getQueue()
	{
		for (int i = (front + 1)%capacity; i <= rear; i++)
			cout << queue[i] << " ";
		cout << endl;
	}
private:
	T *queue;
	int capacity;
	int front;
	int rear;
	Operation lastOp;
	bool isEmpty()
	{
		if (lastOp == myPop && front == rear)
			return true;
		return false;
	}
};

int main()
{
	Queue<int> a(5);
	int temp = 0;
	cout << "Enter the number to Push to the queue.(-1 to end)" << endl;
	cin >> temp;
	while (temp != -1)
	{
		a.Push(temp);
		cin >> temp;
	}
	cout << "Now the queue is:" << endl;
	a.getQueue();
	a.Pop();
	a.Pop();
	a.Pop();
	cout << "After three times pop, the queue is:" << endl;
	a.getQueue();
	system("pause");
}
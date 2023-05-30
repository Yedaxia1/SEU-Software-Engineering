#include <iostream>

using namespace std;

enum Operation{myPush,myPop};//�Զ���ö�����͹�lastOpʹ�á�

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
		if (front == (rear + 1) % capacity)//�ڶ���ֻʣһ���ռ�ʱ���ӱ����пռ�
			DoublingQueue();
		rear = (rear + 1) % capacity;//��β����һλ
		queue[rear] = a;//����������ֵ
		lastOp = myPush;//��lastOp��ֵ��ΪPush.
	}
	void DoublingQueue()
	{
		T *newQueue = new T[capacity * 2];

		int start = (front + 1) % capacity;//��frontĿǰָ���β���߶����һ������ֻ��Ҫ����һ�Ρ�
		if (start < 2)
			copy(queue + start, queue + start + capacity - 1, newQueue);
		else
		{
			copy(queue + start, queue + capacity, newQueue);//�ȿ���front������ռ��β������
			copy(queue, queue + rear + 1, newQueue + capacity - start);//�ٿ�������ռ俪ʼ����β������
		}
		front = 2 * capacity - 1;//�����꣬��ͷָ�����һ���ռ�
		rear = capacity - 2;//�ӱ��ռ�ǰ�����й���capacity-1��Ԫ�أ����Կ����󣬶�βԪ�ص��±�Ϊcapacity-2
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
			lastOp = myPop;//��lastOp��ֵ��ΪPop
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
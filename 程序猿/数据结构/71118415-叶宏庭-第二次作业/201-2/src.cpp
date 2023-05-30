#include <iostream>

using namespace std;
template<class T> class Stack;
template<class T>
class ChainNode {//�ڵ���
	friend class Stack<T>;
public:
	T value;
	ChainNode<T>* link;
	ChainNode() { link = NULL; }
	ChainNode(T element, ChainNode<T>* x=NULL) {
		value = element;
		link = x;
	}
	ChainNode(const ChainNode<T>& temp) {
		if (this != &temp) {
			*this->value = temp.value;
			*this->link = temp.link;
		}
	}
};

template<class T>
class Queue {//�������
private:
	ChainNode<T> *front;//ͷָ��
	ChainNode<T> *rear;//βָ��
public:
	Queue() 
	{
		front = rear = NULL;
	}
	Queue(ChainNode<T> *x)
	{
		front = x;
		rear = x;
	}
	void Push(ChainNode<T> *x)
	{
		if (IsEmpty())//������Ϊ�գ���ͷβ��ָ��x
		{
			front = x;
			rear = x;
		}
		else
		{
			rear->link = x;//���뵽β���棬�����¼����Ԫ�ض�Ϊβ
			rear = x;
		}
	}
	void Pop()
	{
		if (IsEmpty()) throw "The queue is empty, can't pop.";
		else
		{
			ChainNode<T> *temp = front;
			front = front->link;//frontָ������ڵ���һ��Ԫ��
			delete temp;//����ԭ��front�Ŀռ�
		}
	}
	void Get()
	{
		if (IsEmpty()) throw "The queue is empty.";
		else
		{
			ChainNode<T> *temp = front;
			while (temp != rear)
			{
				cout << temp->value << "  ";
				temp = temp->link;
			}
			cout << temp->value << "  ";
			cout << endl;
		}
	}
	bool IsEmpty()
	{
		if (front ==NULL&& rear == NULL)
			return true;
		return false;
	}
};

int main()
{
	Queue<int> myQueue(new ChainNode<int>(1));
	myQueue.Push(new ChainNode<int>(2));
	myQueue.Push(new ChainNode<int>(3));
	myQueue.Push(new ChainNode<int>(4));
	cout << "The queue is :";
	myQueue.Get();
	myQueue.Pop();
	myQueue.Pop();
	cout << "After two times pop, the queue is:";
	myQueue.Get();
	system("pause");
	return 0;
}
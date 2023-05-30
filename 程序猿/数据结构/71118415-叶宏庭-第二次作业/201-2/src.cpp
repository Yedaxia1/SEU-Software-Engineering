#include <iostream>

using namespace std;
template<class T> class Stack;
template<class T>
class ChainNode {//节点类
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
class Queue {//链表队列
private:
	ChainNode<T> *front;//头指针
	ChainNode<T> *rear;//尾指针
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
		if (IsEmpty())//若队列为空，则头尾都指向x
		{
			front = x;
			rear = x;
		}
		else
		{
			rear->link = x;//加入到尾后面，并将新加入的元素定为尾
			rear = x;
		}
	}
	void Pop()
	{
		if (IsEmpty()) throw "The queue is empty, can't pop.";
		else
		{
			ChainNode<T> *temp = front;
			front = front->link;//front指向队列内的下一个元素
			delete temp;//清理原本front的空间
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
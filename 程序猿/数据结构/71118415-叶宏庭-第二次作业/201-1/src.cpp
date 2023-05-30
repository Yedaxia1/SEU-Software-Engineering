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
class Stack {//����ջ
private:
	ChainNode<T> *top;//ͷָ��
public:
	Stack() {};
	Stack(ChainNode<T> *x)
	{
		top = x;
	}
	void Push(ChainNode<T> *x)
	{
		if (IsEmpty())//��ջ�գ���topָ����ջԪ��
			top = x;
		else
		{
			x->link = top;//ջ���գ�����ջԪ��ָ��top���ٽ�topָ����Ԫ��
			top = x;
		}
	}
	void Pop()
	{
		if (IsEmpty()) throw "The stack is empty, can't pop.";
		else
		{
			ChainNode<T> *temp = top;
			top = top->link;//topָ��ջ�ڵ���һ��Ԫ��
			delete temp;//����ԭ��top�Ŀռ�
		}
	}
	void Get()
	{
		if (IsEmpty()) throw "The stack is empty.";
		else
		{
			ChainNode<T> *temp = top;
			while (temp)
			{
				cout << temp->value<<"  ";
				temp = temp->link;
			}
			cout << endl;
		}
	}
	bool IsEmpty()
	{
		return !top;
	}
};

int main()
{
	Stack<int> mystack(new ChainNode<int>(1));
	mystack.Push(new ChainNode<int>(2));
	mystack.Push(new ChainNode<int>(3));
	mystack.Push(new ChainNode<int>(4));
	cout << "The stack is :";
	mystack.Get();
	mystack.Pop();
	mystack.Pop();
	cout << "After two times pop, the stack is:";
	mystack.Get();
	system("pause");
	return 0;
}
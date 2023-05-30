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
class Stack {//链表栈
private:
	ChainNode<T> *top;//头指针
public:
	Stack() {};
	Stack(ChainNode<T> *x)
	{
		top = x;
	}
	void Push(ChainNode<T> *x)
	{
		if (IsEmpty())//若栈空，则top指向入栈元素
			top = x;
		else
		{
			x->link = top;//栈不空，则入栈元素指向top，再将top指向新元素
			top = x;
		}
	}
	void Pop()
	{
		if (IsEmpty()) throw "The stack is empty, can't pop.";
		else
		{
			ChainNode<T> *temp = top;
			top = top->link;//top指向栈内的下一个元素
			delete temp;//清理原本top的空间
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
#include <iostream>

using namespace std;

class ChainNode {//链表节点类
	friend class Chain;
public:
	ChainNode()
	{
		value = 0;
		link = NULL;
	}
	ChainNode(int element, ChainNode * x=NULL)
	{
		value = element;
		link = x;
	}
private:
	int value;
	ChainNode *link;
};

class Chain {
public:
	Chain(ChainNode *x=NULL)
	{
		first = x;
	}
	void insert(ChainNode *x)//插入元素在开头
	{
		x->link = first;
		first = x;
	}
	void deletex(ChainNode *x)
	{
		if (x == first)
			first = first->link;
		else
		{
			ChainNode *temp = first;
			while (temp->link != x)
				temp = temp->link;
			temp->link = x->link;
		}
	}
	int length()
	{
		int counter = 0;
		ChainNode *temp=first;
		while (temp)//若不空，则counter++
		{
			counter++;
			temp = temp->link;
		}
		return counter;
	}
	void Get()
	{
		ChainNode *temp = first;
		while (temp)
		{
			cout << temp->value << "  ";
			temp = temp->link;
		}
		cout << endl;
	}
private:
	ChainNode *first;
};

int main()
{
	ChainNode c1(10);
	ChainNode c2(20);
	ChainNode c3(30);
	ChainNode c4(40);
	Chain myChain(&c1);//加入四个元素到链表中
	myChain.insert(&c2);
	myChain.insert(&c3);
	myChain.insert(&c4);
	cout<<"The chain is:";//输出链表
	myChain.Get();
	myChain.deletex(&c3);//删除c3
	cout<<"After delete c3 the chain is :";//再次输出链表，验证删除操作
	myChain.Get();
	system("pause");
}

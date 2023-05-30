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
private:
	ChainNode *first;
};

int main()
{
	ChainNode c1(10);
	Chain myChain(&c1);
	myChain.insert(new ChainNode(20));
	myChain.insert(new ChainNode(30));
	myChain.insert(new ChainNode(40));//插入四个元素，测试length结果。
	cout <<"Length of the chain is:"<< myChain.length()<<endl;
	system("pause");
}

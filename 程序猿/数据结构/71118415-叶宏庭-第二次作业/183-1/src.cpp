#include <iostream>

using namespace std;

class ChainNode {//����ڵ���
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
	void insert(ChainNode *x)//����Ԫ���ڿ�ͷ
	{
		x->link = first;
		first = x;
	}
	int length()
	{
		int counter = 0;
		ChainNode *temp=first;
		while (temp)//�����գ���counter++
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
	myChain.insert(new ChainNode(40));//�����ĸ�Ԫ�أ�����length�����
	cout <<"Length of the chain is:"<< myChain.length()<<endl;
	system("pause");
}

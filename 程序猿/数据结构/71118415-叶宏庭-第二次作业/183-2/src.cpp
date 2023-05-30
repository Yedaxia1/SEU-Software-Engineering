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
		while (temp)//�����գ���counter++
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
	Chain myChain(&c1);//�����ĸ�Ԫ�ص�������
	myChain.insert(&c2);
	myChain.insert(&c3);
	myChain.insert(&c4);
	cout<<"The chain is:";//�������
	myChain.Get();
	myChain.deletex(&c3);//ɾ��c3
	cout<<"After delete c3 the chain is :";//�ٴ����������֤ɾ������
	myChain.Get();
	system("pause");
}

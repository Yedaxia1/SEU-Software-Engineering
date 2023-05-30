#include <iostream>

using namespace std;

template<class T>
class DoubleLinkedLists;

template<class T>
class Node {//结点类
	friend class DoubleLinkedLists<T>;
private:
	T date;
	Node<T> *left;//左指针
	Node<T> *right;//右指针
public:
	Node(T a=NULL) { date = a; left = this; right = this; }
	~Node() { date = NULL; left = NULL; right = NULL; }
};

template<class T>
class DoubleLinkedLists {
private:
	Node<T> *header;//头指针
public:
	DoubleLinkedLists(Node<T> *a) { header = a; }
	DoubleLinkedLists(DoubleLinkedLists<T> *a)//复制构造函数，连接两个链表时使用
	{
		//利用a.header的值来初始化header，而不是直接将header指向a.header（直接指向会导致错误，此构造函数便是为了避免这个错误）
		header = new Node<T>(a->header->date);
		Node<T> *temp = a->header->right;
		while (temp != a->header)//利用while循环遍历a的整个链表
		{
			this->InsertElement(temp->date);//利用a中对应元素的数值来插入到该链表（直接指向会导致错误）
			temp = temp->right;//temp后移
		}
	}
	void InsertElement(T a)
	{
		Node<T> *temp=new Node<T>(a);//利用数值a构建Node对象，并将其插入到链表中
		InsertElement(temp);
	}
	void InsertElement(Node<T> *a) 
	{ 
		//插入新结点a到header的left位置；
		a->left = header->left;
		header->left->right = a;
		a->right = header;
		header->left = a;
	}
	void Concatenate(DoubleLinkedLists<T> *m)
	{
		DoubleLinkedLists<T> temp(m);//利用上面写的复制构造函数来复制一个m
		InnerConcatenate(temp);//将复制的m与本链表拼接
		m->CleanList();//满足题目要求，在拼接完成后将m清空
	}
	//实现两个链表的拼接
	void InnerConcatenate(DoubleLinkedLists<T> m)
	{
		//取出header的left备用
		Node<T> *temp = this->header->left;
		//1.将m的header接到本链表的最后位置，即header.left.right
		this->header->left->right = m.header;
		//2.将m的最后一个元素接到本链表的header（该题目为双向循环链表）
		m.header->left->right = this->header;
		//3.将本链表的header的left指向m.header.left
		this->header->left = m.header->left;
		//4.将m的header的left指向本链表原本的header.left（用上刚刚取走的temp）
		m.header->left = temp;
	}
	//清空链表
	void CleanList()
	{
		Node<T> *temp1;
		Node<T> *temp2;
		temp1 = header;//从头开始清空
		while (temp1->right!=header)
		{
			temp2 = temp1->right;
			temp1->~Node();
			temp1 = temp2;
		}
		temp1->~Node();
	}
	//输出链表
	void GetElements()
	{
		if (!IsEmpty())//判断是否为空
		{
			Node<T> *temp;
			temp = header;//从头开始输出
			while (temp != header->left)
			{
				cout << temp->date << "  ";
				temp = temp->right;
			}
			cout << temp->date << endl;
		}
		else
			cout << "It's an empty linkedlist!!!" << endl;
	}
	bool IsEmpty()
	{
		if (header->date == NULL)//date为空即链表为空
			return true;
		return false;
	}
};

int main()
{
	//构建五个结点
	Node<int> n1(1);
	Node<int> n2(2);
	Node<int> n3(3);
	Node<int> n4(4);
	Node<int> n5(5);

	//dbl1以n1为header
	DoubleLinkedLists<int> dbl1(&n1);
	//dbl2以n4为header
	DoubleLinkedLists<int> dbl2(&n4);

	//将n2，n3插入dbl1
	dbl1.InsertElement(&n2);
	dbl1.InsertElement(&n3);
	//将n5插入dbl2
	dbl2.InsertElement(&n5);

	//输出初始的dbl1，dbl2
	cout << "Now dbl1:";
	dbl1.GetElements();
	cout << "Now dbl2:";
	dbl2.GetElements();

	//拼接两个链表
	dbl1.Concatenate(&dbl2);

	//拼接完再次输出两个链表
	cout << "After concatenate dbl1:";
	dbl1.GetElements();
	cout << "After concatenate dbl2:";
	dbl2.GetElements();
	system("pause");
	return 0;
}
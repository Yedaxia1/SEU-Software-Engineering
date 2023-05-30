#include <iostream>

using namespace std;

template<class T>
class DoubleLinkedLists;

template<class T>
class Node {//�����
	friend class DoubleLinkedLists<T>;
private:
	T date;
	Node<T> *left;//��ָ��
	Node<T> *right;//��ָ��
public:
	Node(T a=NULL) { date = a; left = this; right = this; }
	~Node() { date = NULL; left = NULL; right = NULL; }
};

template<class T>
class DoubleLinkedLists {
private:
	Node<T> *header;//ͷָ��
public:
	DoubleLinkedLists(Node<T> *a) { header = a; }
	DoubleLinkedLists(DoubleLinkedLists<T> *a)//���ƹ��캯����������������ʱʹ��
	{
		//����a.header��ֵ����ʼ��header��������ֱ�ӽ�headerָ��a.header��ֱ��ָ��ᵼ�´��󣬴˹��캯������Ϊ�˱����������
		header = new Node<T>(a->header->date);
		Node<T> *temp = a->header->right;
		while (temp != a->header)//����whileѭ������a����������
		{
			this->InsertElement(temp->date);//����a�ж�ӦԪ�ص���ֵ�����뵽������ֱ��ָ��ᵼ�´���
			temp = temp->right;//temp����
		}
	}
	void InsertElement(T a)
	{
		Node<T> *temp=new Node<T>(a);//������ֵa����Node���󣬲�������뵽������
		InsertElement(temp);
	}
	void InsertElement(Node<T> *a) 
	{ 
		//�����½��a��header��leftλ�ã�
		a->left = header->left;
		header->left->right = a;
		a->right = header;
		header->left = a;
	}
	void Concatenate(DoubleLinkedLists<T> *m)
	{
		DoubleLinkedLists<T> temp(m);//��������д�ĸ��ƹ��캯��������һ��m
		InnerConcatenate(temp);//�����Ƶ�m�뱾����ƴ��
		m->CleanList();//������ĿҪ����ƴ����ɺ�m���
	}
	//ʵ�����������ƴ��
	void InnerConcatenate(DoubleLinkedLists<T> m)
	{
		//ȡ��header��left����
		Node<T> *temp = this->header->left;
		//1.��m��header�ӵ�����������λ�ã���header.left.right
		this->header->left->right = m.header;
		//2.��m�����һ��Ԫ�ؽӵ��������header������ĿΪ˫��ѭ������
		m.header->left->right = this->header;
		//3.���������header��leftָ��m.header.left
		this->header->left = m.header->left;
		//4.��m��header��leftָ������ԭ����header.left�����ϸո�ȡ�ߵ�temp��
		m.header->left = temp;
	}
	//�������
	void CleanList()
	{
		Node<T> *temp1;
		Node<T> *temp2;
		temp1 = header;//��ͷ��ʼ���
		while (temp1->right!=header)
		{
			temp2 = temp1->right;
			temp1->~Node();
			temp1 = temp2;
		}
		temp1->~Node();
	}
	//�������
	void GetElements()
	{
		if (!IsEmpty())//�ж��Ƿ�Ϊ��
		{
			Node<T> *temp;
			temp = header;//��ͷ��ʼ���
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
		if (header->date == NULL)//dateΪ�ռ�����Ϊ��
			return true;
		return false;
	}
};

int main()
{
	//����������
	Node<int> n1(1);
	Node<int> n2(2);
	Node<int> n3(3);
	Node<int> n4(4);
	Node<int> n5(5);

	//dbl1��n1Ϊheader
	DoubleLinkedLists<int> dbl1(&n1);
	//dbl2��n4Ϊheader
	DoubleLinkedLists<int> dbl2(&n4);

	//��n2��n3����dbl1
	dbl1.InsertElement(&n2);
	dbl1.InsertElement(&n3);
	//��n5����dbl2
	dbl2.InsertElement(&n5);

	//�����ʼ��dbl1��dbl2
	cout << "Now dbl1:";
	dbl1.GetElements();
	cout << "Now dbl2:";
	dbl2.GetElements();

	//ƴ����������
	dbl1.Concatenate(&dbl2);

	//ƴ�����ٴ������������
	cout << "After concatenate dbl1:";
	dbl1.GetElements();
	cout << "After concatenate dbl2:";
	dbl2.GetElements();
	system("pause");
	return 0;
}
#include <iostream>

using namespace std;
template<class T>
class Stack {//ջ�࣬���ڱ���tree
private:
	T * term;
	int capacity;
	int top;
public:
	Stack(int a=100)
	{
		capacity = a;
		top = -1;
		term = new T[capacity];
	}
	void Push(T &a)
	{
		term[++top] = a;
	}
	void Pop()
	{
		term[top--].~T();
	}
	T & Top()
	{
		return term[top];
	}
	void Get()
	{
		for (int i = 0; i <= top; i++)
			cout << term[i] << "  ";
		cout << endl;
	}
	bool IsEmpty()
	{
		if (top == -1)
			return true;
		return false;
	}
};

template<class T>
class Tree;

template<class T>
class TreeNode {
	friend class Tree<T>;
private:
	T data;//�������
	TreeNode<T> *leftChlid;//����
	TreeNode<T> *rightChlid;//�Һ���
public:
	TreeNode(T a=NULL) { data = a; }
};

template<class T>
class Tree {
private:
	TreeNode<T> *root;//�����
public:
	Tree(TreeNode<T> *a) { root = a; }
	bool IsEmpty()//�ж�tree�Ƿ�Ϊ��
	{
		if (!root)
			return true;
		return false;
	}
	//�����㣬��������a��ֵ����������λ�ã�
	//�������0������������1��������������a={0��1��0}������뵽root.leftChild.rightChild.leftChild��λ�á�
	//mΪҪ����Ľ��
	void InsertNode(char a[],int size,TreeNode<T> *m)
	{
		TreeNode<T> *currentNode = root;
		if (size == 1)
		{
			if (a[0] == 0)
				currentNode->leftChlid = m;
			else
				currentNode->rightChlid = m;
			return;
		}
		for (int i = 0; i < size -1; i++)
		{
			if (a[i] == 0)
				currentNode = currentNode->leftChlid;
			else
				currentNode = currentNode->rightChlid;
		}
		if (a[size - 1] == 0)
			currentNode->leftChlid = m;
		else
			currentNode->rightChlid = m;
	}
	void Visit(TreeNode<T> *m)//����ĳһ�����
	{
		cout<<m->data<<" ";
	}
	TreeNode<T> *GetRoot()
	{
		return root;
	}
	class InorderIterator {//�ڲ��ࣨ��������
	public:
		InorderIterator(TreeNode<T> *root) { currentNode = root; }
		T* Next()//�����һ�����
		{
			while (currentNode)//�ж�currentNode�Ƿ�Ϊ��
			{
				s.Push(currentNode);//ѹջ
				currentNode = currentNode->leftChlid;//currentNodeָ������
			}
			if (s.IsEmpty()) return 0;//�ж�ջ�Ƿ�Ϊ�գ�ջ����������
			currentNode = s.Top();//��ȡջ��Ԫ��
			s.Pop();//��ջ
			T& temp = currentNode->data;//���ʱ��η��ʵ���������
			currentNode = currentNode->rightChlid;//currentNodeָ���Һ���
			return &temp;
		}
	private:
		Stack<TreeNode<T>*>  s;
		TreeNode<T> *currentNode;
	} ;
};

int main()
{
	//������ʱʹ�õ�����
	char a1[] = { 0};
	char a2[] = { 1};
	char a3[] = { 0 , 0};
	char a4[] = { 0 , 1};
	char a5[] = { 1 , 0};

	//����root���
	TreeNode<int> *r=new TreeNode<int>(4);

	//��root���Ϊ����������
	Tree<int> *myTree=new Tree<int>(r);
	
	//�����㵽����
	myTree->InsertNode(a1, 1, new TreeNode<int>(2));
	myTree->InsertNode(a2, 1, new TreeNode<int>(6));
	myTree->InsertNode(a3, 2, new TreeNode<int>(1));
	myTree->InsertNode(a4, 2, new TreeNode<int>(3));
	myTree->InsertNode(a5, 2, new TreeNode<int>(5));

	//����������
	Tree<int>::InorderIterator i1(myTree->GetRoot());
	cout << "Traverse by InnerIterator (in inorder):";

	//������
	int *temp = i1.Next();
	while (temp != 0)
	{
		cout << *temp << " ";
		temp = i1.Next();
	}
	system("pause");
	return 0;
}
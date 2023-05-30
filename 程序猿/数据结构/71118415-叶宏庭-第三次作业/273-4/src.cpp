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
class MyQueue {
private:
	T *term;
	int front;
	int rear;
	int capacity;
public:
	MyQueue(int s=100)
	{
		capacity = s;
		term = new T[capacity];
		front = rear = 0;
	}
	bool IsEmpty()
	{
		if (front == rear == 0)
			return true;
		return false;
	}
	void Push(T &a)
	{
		term[rear++] = a;
	}
	T & Front()
	{
		return term[front];
	}
	void Pop()
	{
		term[front++].~T();
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
	~Tree()
	{
		InorderIterator i1(root);
		TreeNode<T> * temp;
		while (temp = i1.Next())
			delete temp;
	}
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
	void CreatByArray(T arrays[],int size)
	{
		MyQueue<TreeNode<T> *> qc;
		TreeNode<T> *currentNode = root;
		int sub = 1;
		while (1)
		{
			if (sub == size)
				return;
			currentNode->data = arrays[sub];
			if (sub * 2 < size)
			{
				currentNode->leftChlid = new TreeNode<T>();
				qc.Push(currentNode->leftChlid);
			}
			if (sub * 2 + 1 < size)
			{
				currentNode->rightChlid = new TreeNode<T>();
				qc.Push(currentNode->rightChlid);
			}
			currentNode = qc.Front();
			qc.Pop();
			sub++;
		}
	}
	int LeafNodeNumber()//��ȡҶ�ӽ�����
	{
		InorderIterator i1(root);//����������
		int counter = 0;//����
		TreeNode<T> * temp;
		while (temp = i1.Next())//ʹ�õ���������
		{
			if (!temp->leftChlid)//����ǰ��㲻�������ӣ���ý��ΪҶ�ӽ��
				counter++;
		}
		return counter;
	}
	//�ǵݹ�ǰ�����
	void nonrecursivePreorder()
	{
		Stack<TreeNode<T>*>  s;
		TreeNode<T> *currentNode = root;
		while (1)
		{
			while (currentNode)
			{
				if (currentNode->rightChlid)//����ǰ������rightChlid����rightChlidѹջ���Ա�leftChild������Ϻ󣬿��Դ�ջ��ȡ��rightChild
					s.Push(currentNode->rightChlid);
				Visit(currentNode);//ǰ��������ȷ��ʵ�ǰ���
				currentNode = currentNode->leftChlid;//�������
			}
			if (s.IsEmpty()) return;
			currentNode = s.Top();//��ջ��ȡ�����һ�δ��ڵ�rightChild
			s.Pop();//ȡ�������rightChild�󣬳�ջ
		}
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
		Stack<TreeNode<T>*>  s;
		T* NextData()//�����һ�����
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
		TreeNode<T> * Next()
		{
			while (currentNode)//�ж�currentNode�Ƿ�Ϊ��
			{
				s.Push(currentNode);//ѹջ
				currentNode = currentNode->leftChlid;//currentNodeָ������
			}
			if (s.IsEmpty()) return 0;//�ж�ջ�Ƿ�Ϊ�գ�ջ����������
			currentNode = s.Top();//��ȡջ��Ԫ��
			s.Pop();//��ջ
			TreeNode<T> * temp = currentNode;//
			currentNode = currentNode->rightChlid;//currentNodeָ���Һ���
			return temp;
		}
	private:
		TreeNode<T> *currentNode;
	} ;
};

int main()
{
	////������ʱʹ�õ�����
	//char a1[] = { 0};
	//char a2[] = { 1};
	//char a3[] = { 0 , 0};
	//char a4[] = { 0 , 1};
	//char a5[] = { 1 , 0};

	////����root���
	//TreeNode<int> *r=new TreeNode<int>(4);

	////��root���Ϊ����������
	//Tree<int> *myTree=new Tree<int>(r);
	//
	////�����㵽����
	//myTree->InsertNode(a1, 1, new TreeNode<int>(2));
	//myTree->InsertNode(a2, 1, new TreeNode<int>(6));
	//myTree->InsertNode(a3, 2, new TreeNode<int>(1));
	//myTree->InsertNode(a4, 2, new TreeNode<int>(3));
	//myTree->InsertNode(a5, 2, new TreeNode<int>(5));

	////����������
	//Tree<int>::InorderIterator i1(myTree->GetRoot());
	//cout << "Traverse by InnerIterator (in inorder):";

	////���������
	//int *temp = i1.Next();
	//while (temp != 0)
	//{
	//	cout << *temp << " ";
	//	temp = i1.Next();
	//}

	////ǰ�����
	//myTree->nonrecursivePreorder();
	TreeNode<int> *r = new TreeNode<int>();
	Tree<int> *myTree = new Tree<int>(r);

	int myArray[] = { 0,1,2,3,4,5,6,7,8 };
	myTree->CreatByArray(myArray, sizeof(myArray) / sizeof(int));//ʹ�����鴴����
	cout << "The tree is (preorder):";
	myTree->nonrecursivePreorder();//��ӡ��
	myTree->~Tree();//����
	system("pause");
	return 0;
}
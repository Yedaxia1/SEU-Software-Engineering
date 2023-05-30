#include <iostream>

using namespace std;

template<class T>
class Stack {//ջ�࣬���ڱ���tree
private:
	T * term;
	int capacity;
	int top;
public:
	Stack(int a = 100)
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
	MyQueue(int s = 100)
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
	bool leftThread;
	bool rightThread;
	TreeNode<T> *leftChlid;//����
	TreeNode<T> *rightChlid;//�Һ���
public:
	TreeNode(T a=NULL) 
	{ 
		data = a;
		leftThread = rightThread = false;
	}
};

template<class T>
class Tree {
private:
	TreeNode<T> * root;//�����
public:
	Tree(TreeNode<T> *a)
	{
		root = new TreeNode<T>();
		root->rightChlid = root;	
		root->leftChlid = a;
	}
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
	void CreatByArray(T arrays[],int size)
	{
		MyQueue<TreeNode<T> *> qc;
		TreeNode<T> *currentNode = root->leftChlid;
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
	void CreatThread()
	{
		InorderIterator i1(root->leftChlid, root);
		TreeNode<T> *temp2=root;
		TreeNode<T> *temp3=i1.Next();
		TreeNode<T> *temp1 =temp3;
		while (1)
		{
			temp3 = i1.Next();
			if (!temp1->leftChlid)
			{
				temp1->leftThread = true;
				temp1->leftChlid = temp2;
			}
			if (!temp1->rightChlid)
			{
				temp1->rightThread = true;
				temp1->rightChlid = temp3;
			}
			if (!temp3)
				break;
			temp2 = temp1;
			temp1 = temp3;
		}
		temp1->rightChlid = root;
	}
	void InsertNodeAfterS(TreeNode<T> *s, TreeNode<T> *a)
	{
		InorderIterator i1(root->leftChlid, root);
		TreeNode<T> *temp = i1.NextData();
		while (temp)
		{
			if (temp->data == s->data)
				break;
			temp = i1.NextData();
		}
		a->leftChlid = temp->leftChlid;
		a->leftThread = temp->leftThread;
		a->rightChlid = temp;
		a->rightThread = true;
		temp->leftChlid->rightChlid = a;
		temp->leftChlid = a;
		temp->leftThread = false;
	}
	void GetTree()
	{
		InorderIterator i1(root->leftChlid,root);
		TreeNode<T> *  temp = i1.NextData();
		while (temp)
		{
			cout << temp->data << " ";
			temp = i1.NextData();
		}
			
	}
	int LeafNodeNumber()//��ȡҶ�ӽ�����
	{
		InorderIterator i1(root->leftChlid,root);//����������
		int counter = 0;//����
		TreeNode<T> * temp;
		while (temp = i1.Next())//ʹ�õ���������
		{
			if (!temp->leftChlid)//����ǰ��㲻�������ӣ���ý��ΪҶ�ӽ��
				counter++;
		}
		return counter;
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
		InorderIterator(TreeNode<T> *r, TreeNode<T> *r1) { currentNode = r; root1 = currentNode2 = r1; }
		Stack<TreeNode<T>*>  s;
		TreeNode<T> * NextData()//�����һ�����
		{
			TreeNode<T> *temp = currentNode2->rightChlid;
			if (!currentNode2->rightThread)
				while (!temp->leftThread) temp = temp->leftChlid;
			currentNode2 = temp;
			if (currentNode2 == root1) return 0;
			else return currentNode2;
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
		TreeNode<T> *root1;
		TreeNode<T> *currentNode;
		TreeNode<T> *currentNode2;
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
	myTree->CreatThread();
	cout << "Initial tree(inorder):";
	myTree->GetTree();
	cout << endl;
	myTree->InsertNodeAfterS(new TreeNode<int>(5), new TreeNode<int>(9));
	cout << "Insert 9 after 5, the tree is:";
	myTree->GetTree();
	system("pause");
	return 0;
}
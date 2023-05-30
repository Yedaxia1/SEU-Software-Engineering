#include <iostream>
#include <string>

using namespace std;

class TreeNode {
public:
	TreeNode()
	{
		key = -1;
		value = -5;
	}
	TreeNode(int k, int v)
	{
		key = k;
		value = v;
	}
	int key;
	int value;
};

class LoserTree {
public:
	LoserTree(int k,TreeNode *a)
	{
		terms = new TreeNode[2*k];
		for (int i = 1; i <= k; i++)
		{
			InsertNode(i, a[i - 1]);
		}
	}
	TreeNode GetTop()
	{
		return terms[0];
	}
	//������һ��Ԫ�أ����Ѿ�ȡ�ߵ�һ���������������еڶ���ȡ��
	void InsertNode(int k, TreeNode &a)
	{//k��ʾ�����Ǹ�����
		int sub = k + 7;
		//������Ԫ��
		terms[sub] = a;
		TreeNode temp;
		//ѭ���Ƚϣ������ع�
		while (sub > 1)
		{
			//����Ԫ�����ȼ�>���ڵ����ȼ�������Ԫ�ؼ���������
			if (a.value < terms[sub / 2].value)
				sub /= 2;
			else//����Ԫ�����ȼ�<���ڵ����ȼ�������Ԫ�ط��븸�ڵ�λ�ã����ڵ�Ԫ�ؼ���������
			{
				temp = terms[sub / 2];
				terms[sub / 2] = a;
				a = temp;
				sub /= 2;
			}
			if (sub == 1)
				terms[0] = a;
		}
	}
private:
	TreeNode *terms;
};

void main()
{
	TreeNode *a = new TreeNode[8]{
		TreeNode(1, 10),
		TreeNode(2, 9),
		TreeNode(3, 20),
		TreeNode(4, 15),
		TreeNode(5, 8),
		TreeNode(6, 9),
		TreeNode(7, 90),
		TreeNode(8, 17)
	};

	//������������������
	LoserTree t2(8,a);
	
	return;
}
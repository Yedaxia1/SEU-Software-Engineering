#include <iostream>
#include <string>

using namespace std;

class TreeNode {
public:
	TreeNode()
	{
		key = -1;
		value = 1000;
	}
	TreeNode(int k, int v)
	{
		key = k;
		value = v;
	}
	int key;
	int value;
};

class WinnerTree {
public:
	WinnerTree()
	{
		terms = new TreeNode[16];
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
		//ѭ���Ƚϣ������ع�
		while (sub >= 1)
		{
			//���õ�Ϊż���У����ֵ�Ϊsub+1
			if (sub % 2 == 0)
			{
				//����Ԫ�����ȼ�>�ֵܵ����ȼ�����ΪΪ��������������С�����ȼ������󣩣����׸���Ϊ��Ԫ��
				if (a.value < terms[sub + 1].value)
				{
					sub /= 2;
					terms[sub] = a;
				}
				else {//����Ԫ�����ȼ�<�ֵܵ����ȼ������ڸ���
					a = terms[sub + 1];
					terms[sub / 2] = terms[sub + 1];
					sub /= 2;
				}
			}
			else {//���õ�Ϊ�����У����ֵ�Ϊsub-1
				//���²���ͬ�ϣ�������Ϊ�ֵ��±���㲻ͬ��������if��else������
				if (a.value < terms[sub - 1].value)
				{
					sub /= 2;
					terms[sub] = a;
				}
				else {
					a = terms[sub - 1];
					terms[sub / 2] = terms[sub - 1];
					sub /= 2;
				}
			}
		}
		terms[0] = terms[1];
	}
private:
	TreeNode *terms;
};

class LoserTree {
public:
	LoserTree()
	{
		terms = new TreeNode[16];
		for (int i = 0; i < 16; i++)
			terms[i].value = -5;
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
	//����8�����
	TreeNode n1(1, 10);
	TreeNode n2(2, 9);
	TreeNode n3(3, 20);
	TreeNode n4(4, 15);
	TreeNode n5(5, 8);
	TreeNode n6(6, 9);
	TreeNode n7(7, 90);
	TreeNode n8(8, 17);

	//����ʤ�����������μ���8�����
	WinnerTree t1;
	t1.InsertNode(n1.key, n1);
	t1.InsertNode(n2.key, n2);
	t1.InsertNode(n3.key, n3);
	t1.InsertNode(n4.key, n4);
	t1.InsertNode(n5.key, n5);
	t1.InsertNode(n6.key, n6);
	t1.InsertNode(n7.key, n7);
	t1.InsertNode(n8.key, n8);

	//������������������
	LoserTree t2;
	t2.InsertNode(n1.key, n1);
	t2.InsertNode(n2.key, n2);
	t2.InsertNode(n3.key, n3);
	t2.InsertNode(n4.key, n4);
	t2.InsertNode(n5.key, n5);
	t2.InsertNode(n6.key, n6);
	t2.InsertNode(n7.key, n7);
	t2.InsertNode(n8.key, n8);
	return;
}
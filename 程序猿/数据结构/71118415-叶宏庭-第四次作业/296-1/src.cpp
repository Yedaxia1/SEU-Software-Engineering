#include <iostream>
#include <string>

using namespace std;

template<class K, class E>
class TreeNode {
public:
	TreeNode(K k,E v)
	{
		key = k;
		value = v;
	}
	E GetValue()
	{
		return value;
	}
	K key;
	E value;
	TreeNode *parent;
	TreeNode *leftChlid;
	TreeNode *rightChild;
};

template<class K, class E>
class BinarySearchTree {
public:
	BinarySearchTree(){}
	BinarySearchTree(TreeNode<K,E> &r) { root = &r; };
	TreeNode<K, E> * Get(const K &k)
	{
		return Get(root, k);
	}
	void Insert(const TreeNode<K, E> &thePair)
	{
		TreeNode<K, E> *p = root, *pp = 0;
		while (p)
		{
			pp = p;
			if (thePair.key < p->key) p = p->leftChlid;
			else if (thePair.key > p->key) p = p->rightChild;
			else {
				p->value = thePair.value;
				return;
			}
		}

		p = new TreeNode<K, E>(thePair);
		if (root)
			if (thePair.key < pp->key) { pp->leftChlid = p; p->parent = pp; }
			else { pp->rightChild = p; p->parent = pp ; }
		else root = p;
	}
	void Delete(const K&k)
	{
		TreeNode<K, E>* p = Get(k);
		if (!p->leftChlid && !p->rightChild) {
			if (p == p->parent->leftChlid) p->parent->leftChlid = NULL;
			else p->parent->rightChild = NULL;
		}
		else if (!p->leftChlid&&p->rightChild) *p = *p->rightChild;
		else if (p->leftChlid && !p->rightChild) p = p->leftChlid;
		else {
			TreeNode<K, E> *current1= p->leftChlid;
			TreeNode<K, E> *current2=current1;
			while (current1)
			{
				if (current1->rightChild)
				{
					current2 = current1;
					current1 = current1->rightChild;
				}
				else
				{
					current1->leftChlid = p->leftChlid;
					current1->rightChild = p->rightChild;
					p->~TreeNode();
					p = current1;
					current2->rightChild = NULL;
					break;
				}
			}

		}

	}
	bool IsEmpty() { return root; };
private:
	TreeNode<K, E> * Get(TreeNode<K, E> * p, const K &k)
	{
		if (!p) return 0;
		if (k < p->key) return Get(p->leftChlid, k);
		if (k > p->key) return Get(p->rightChild, k);
		return p;
	}
	TreeNode<K, E> *root;
};

int main()
{
	TreeNode<int, string> n1(1, "一");
	TreeNode<int, string> n2(2, "二");
	TreeNode<int, string> n3(3, "三");
	TreeNode<int, string> n4(4, "四");
	TreeNode<int, string> n5(5, "五");
	TreeNode<int, string> n6(6, "六");

	BinarySearchTree<int,string> t1(n3);
	t1.Insert(n1);
	t1.Insert(n2);
	t1.Insert(n4);
	t1.Insert(n5);
	t1.Insert(n6);

	t1.Delete(2);
	t1.Delete(4);
	system("pause");
	return 0;
}
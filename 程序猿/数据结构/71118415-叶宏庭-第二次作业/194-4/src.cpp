#include<iostream>
#include<iterator>
using namespace std;

template<class T> class Chain;
template<class T>
class ChainNode {//节点类
	friend class Chain<T>;
public:
	T value;
	ChainNode<T>* link;
	ChainNode() { link = NULL; }
	ChainNode(T element, ChainNode<T>* x) {
		value = element;
		link = x;
	}
	ChainNode(const ChainNode<T>& temp) {
		if (this != &temp) {
			*this->value = temp.value;
			*this->link = temp.link;
		}
	}
};

template<class T>
class ChainIterator : public iterator<input_iterator_tag, T> {//链表迭代器类，继承iterator类
private:
	ChainNode<T>* current;
	int sub;
public:
	int getTestInt() const { return (*this).sub; }

	~ChainIterator() = default;
	ChainIterator(ChainNode<T>* startNode = 0, int x = 0) {
		current = startNode;
		sub = x;
	}
	ChainIterator(const ChainIterator<T>& temp) {
		current = temp.current;
		sub = temp.sub;
	}

	//为copy函数提供运算符重载
	T& operator*()const { return current->value; }//取值运算符*
	ChainNode<T>** operator&() { return &current; }
	T* operator->()const { return &current->value; }

	//自增运算符重载
	ChainIterator<T>& operator ++() {//前加加
		current = current->link;
		return *this;
	}
	ChainIterator<T> operator ++(int) {//后加加
		ChainIterator<T> old = *this;
		current = current->link;
		return old;
	}

	ChainIterator<T>& operator=(const ChainIterator<T>& right) noexcept {//赋值运算符重载
		if (&right == this) return *this;
		delete current;
		this->current = right.current;
		this->sub = right.sub;
		return *this;
	}
	//copy函数需要用到 != 重载
	bool operator!=(const ChainIterator<T> right)const {
		return current != right.current;
	}
	bool operator==(const ChainIterator<T> right)const {
		return current == right.current;
	}
};
template<class T>
class Chain {//链表类
private:
	ChainNode<T>* first;//头指针
public:
	//构造函数
	Chain() { first = NULL; }
	Chain(ChainNode<T>* x) { first = x; }
	//析构
	~Chain() {
		while (first) {
			ChainNode<T>* temp = first;
			first = first->link;
			delete temp;
		}
	}
	//将数组转换成链表
	void CreatByArray(T *arrary, int n) {
		if (n < 1) return;
		ChainNode<T>* temp = new ChainNode<T>(arrary[0], NULL);
		first = temp;
		for (int i = 1; i < n; i++) {
			ChainNode<T>* t = new ChainNode<T>(arrary[i], NULL);
			temp->link = t;
			temp = temp->link;
		}
	}
	//求链表长度
	int length() {
		ChainNode<T>* temp = first;
		int n = 0;
		while (temp) {
			n++;
			temp = temp->link;
		}
		return n;
	}
	void Get() {
		ChainNode<T>* temp = first;
		while (temp) {
			cout << temp->value << ((temp->link) ? " -> " : "");
			temp = temp->link;
		}
		cout << endl;
	}
	ChainNode<T>* getFirst() { return first; }
	ChainIterator<T> getSub(int x)
	{
		ChainNode<T> *temp = first;
		int counter = 0;
		for (; counter < x; counter++)
			temp = temp->link;
		return ChainIterator<T>(temp);
	}
	ChainIterator<T> begin() { return ChainIterator<T>(first); }
	ChainIterator<T> end() {
		ChainIterator<T> it(first);
		for (int i = 0; i < length(); i++) it++;
		return it;
	}
};
int main()
{
	int a[] = { 1,2,3,4,5,6,7,8 ,9,10};
	Chain<int> myChain;
	myChain.CreatByArray(a, 10);
	int sum = 0;
	ChainIterator<int> c1 = myChain.begin();
	ChainIterator<int> c2 = myChain.getSub(5);
	for (int i = 0; i < myChain.length() - 5; i++)
	{
		sum += *c1**c2;
		c1++;
		c2++;
	}
	cout <<"The sum of xi*x(i+5) (i from 1 to n-5) is:"<< sum;
	system("pause");
}
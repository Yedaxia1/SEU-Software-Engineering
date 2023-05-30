
template<class T>
void adjust(T* a, const int root, const int n) {
	T e = a[root];
	int i;
	for (i = 2 * root; i <= n; i *= 2) {
		if (i < n && a[i] < a[i + 1])i++;
		if (e >= a[i])break;
		a[i / 2] = a[i];
	}
	a[i / 2] = e;
}

//堆排序
template<class T>
void heapSort(T *list, const int n) {
	stack<T> a;
	for (int i = n / 2; i >= 1; i--)
		adjust(list, i, n);
	for (int i = n - 1; i >= 1; i--) {
		a.push(list[1]);
		swap(list[1], list[i + 1]);
		adjust(list, 1, i);
	}
	a.push(list[1]);
	while (!a.empty())
	{
		cout << a.top() << " ";
		a.pop();
	}
}


/*
P422-1,3,5
(1)对表(12, 2, 16, 30，8, 28, 4, 10, 20, 6，18)使用RadixSort(见程序7. 15)进行排序，写出每趟过后表的状态。选择r=10。
(3)例7.8中对数字进行排序的RadixSort算法是稳定的吗?
(5)现有n条记录，关键字为区间[0, n2)内的整数。可以使用堆排序或归并排序在O(nlogn)时间内完成对它们的排序。单一关键字的基数排序(d=1, r= n2)将花费的O(n2)时间。请问如何将关键字分解为两个子关键字，从而令基数排序仅仅需要O(n)的时间就可以完成对n条记录的排序? (提示:每个关键字K;都可以表示为K;=K}n+K,其中K}和K?是区间[0, n)内的整数。)
*/


int Digit(int e, int i, int r) {
	int k;
	int j;
	for (j = 0; j <= r; j++) {
		if (j * r <= e && (j + 1)*r > e) {
			k = e % r;
			j = e / r;
			break;
		}
	}
	if (i == 1) {
		return k;
	}
	else {
		return j;
	}
}

int* link;
int radixSort(int * list, const int digit, const int radix, const int n) {
	int *e, *f;
	e = new int[radix];
	f = new int[radix];
	link = new int[n];
	int first = 0;
	for (int i = 0; i < n - 1; i++)
		link[i] = i + 1;
	link[n - 1] = -1;
	for (int i = digit - 1; i >= 0; i--) {
		fill(f, f + radix, -1);
		fill(e, e + radix, 0);
		int current = first;
		for (; current != -1; current = link[current]) {
			int k = Digit(list[current], i, radix);
			if (f[k] == -1)
				f[k] = current;
			else
				link[e[k]] = current;
			e[k] = current;
		}
		int j;
		for (j = 0; f[j] == -1; j++);
		first = f[j];
		int last = e[j];
		int k;
		for (k = j + 1; k < radix; k++) {
			if (f[k] != -1) {
				link[last] = f[k];
				last = e[k];
			}
		}
		link[last] = -1;
		cout << "每趟排序之后的顺序为：" << endl;
		for (int s = first; s != -1; s = link[s])
			cout << list[s] << " ";
		cout << endl;
	}
	return first;
}
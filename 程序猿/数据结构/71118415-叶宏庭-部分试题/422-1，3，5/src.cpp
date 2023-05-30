
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

//������
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
(1)�Ա�(12, 2, 16, 30��8, 28, 4, 10, 20, 6��18)ʹ��RadixSort(������7. 15)��������д��ÿ�˹�����״̬��ѡ��r=10��
(3)��7.8�ж����ֽ��������RadixSort�㷨���ȶ�����?
(5)����n����¼���ؼ���Ϊ����[0, n2)�ڵ�����������ʹ�ö������鲢������O(nlogn)ʱ������ɶ����ǵ����򡣵�һ�ؼ��ֵĻ�������(d=1, r= n2)�����ѵ�O(n2)ʱ�䡣������ν��ؼ��ַֽ�Ϊ�����ӹؼ��֣��Ӷ���������������ҪO(n)��ʱ��Ϳ�����ɶ�n����¼������? (��ʾ:ÿ���ؼ���K;�����Ա�ʾΪK;=K}n+K,����K}��K?������[0, n)�ڵ�������)
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
		cout << "ÿ������֮���˳��Ϊ��" << endl;
		for (int s = first; s != -1; s = link[s])
			cout << list[s] << " ";
		cout << endl;
	}
	return first;
}
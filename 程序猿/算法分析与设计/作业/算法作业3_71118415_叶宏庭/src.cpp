#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
# include <string>
#include <vector>
using namespace std;
int maxSum(int N, int *b);

int main()
{
	int N;
	cin >> N;
	int A[101][101];

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}
	int result = A[1][1];
	for (int i = 1; i <= N; i++) {//起始行
		int b[101] = { 0 };
		for (int j = i; j <= N; j++) {//终点行
			for (int k = 1; k <= N; k++) {//计算列和
				b[k] += A[j][k];
			}
			int maxsum = maxSum(N, b);
			if (maxsum > result)
				result = maxsum;
		}
	}
	cout << result;
	return 0;
}

int maxSum(int N, int *b) {
	int sum = 0;
	int tem = b[1];
	for (int i = 2; i <= N; i++) {
		if (tem > 0) {
			tem += b[i];
		}
		if (tem <= 0)
			tem = b[i];
		if (tem > sum)
		{
			sum = tem;
		}
	}
	return sum;
}
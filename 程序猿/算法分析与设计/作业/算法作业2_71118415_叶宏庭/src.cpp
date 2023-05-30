#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int test_cases, N;

const double INF = 2000000000;
const int maxn = 200010;
double ans = INF;

struct point
{
	double x, y;
	int chac;
	point(double xx, double yy, int c)
	{
		x = xx;
		y = yy;
		chac = c;
	}
	point()
	{
	}
}points[maxn], temp[maxn];

bool cmpx(point A, point B)
{
	return A.x < B.x;
}

double distance(point A, point B)
{
	if (A.chac == B.chac) return INF;
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

double Closest(int l, int r)
{
	if (l >= r)
	{
		return INF;
	}
	else
	{
		int mid = (l + r) >> 1;
		double midx = points[mid].x;
		double d1, d2, d;
		d1 = Closest(l, mid);
		d2 = Closest(mid + 1, r);
		d = min(d1, d2);
		ans = min(ans, d);
		{
			int k = 0, i = l, j = mid + 1;
			while (i <= mid && j <= r)
			{
				if (points[i].y <= points[j].y)
					temp[k++] = points[i++];
				else
					temp[k++] = points[j++];
			}
			while (i <= mid) temp[k++] = points[i++];
			while (j <= r) temp[k++] = points[j++];
			for (int i = 0, j = l; i < k; i++, j++) points[j] = temp[i];
		}
		int k = 0;
		for (int i = l; i <= r; i++)
			if (points[i].x >= midx - ans && points[i].x <= midx + ans)
				temp[k++] = points[i];
		for (int i = 0; i < k; i++)
			for (int j = i + 1; j < k; j++)
			{
				if (temp[j].y - temp[i].y > d)
					break;
				ans = min(ans, distance(temp[i], temp[j]));
			}
		return ans;
	}
}

int main()
{
	cin >> test_cases;

	for (int k = 1; k <= test_cases; k++)
	{
		cin >> N;
		ans = INF;
		for (int i = 0; i < N; i++)
		{
			cin >> points[i].x >> points[i].y;
			points[i].chac = 1;
		}
		for (int i = N; i < 2 * N; i++)
		{
			cin >> points[i].x >> points[i].y;
			points[i].chac = 2;
		}
		sort(points, points + 2 * N, cmpx);
		printf("%.3lf\n", Closest(0, 2 * N - 1));
	}
	return 0;
}
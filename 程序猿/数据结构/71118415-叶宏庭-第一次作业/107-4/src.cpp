#include <iostream>
using namespace std;

class SparseMatrix;
class MatrixTerm {
	friend class SparseMatrix;
	void set(int r, int c, int v)
	{
		row = r;
		col = c;
		value = v;
	}
private:
	int row, col, value;
};

class SparseMatrix {
public:
	SparseMatrix(int r, int c, int t)
	{
		rows = r;
		cols = c;
		terms = t;
		capacity = 0;
		smArray = new MatrixTerm[terms];
	}
	void inputElements(int r, int c, int v)
	{
		if (capacity < terms)
			smArray[capacity++].set(r, c, v);
	}
	void outputMatrix()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				for (int k = 0; k < terms; k++)
				{
					if (smArray[k].row == i && smArray[k].col == j)
					{
						cout << smArray[k].value << "  ";
						break;
					}
					else if (smArray[k].row > i)
					{
						cout << 0 << "  ";
						break;
					}
				}
			}
			cout << endl;
		}
	}
	SparseMatrix FastTranspose()
	{
		SparseMatrix b(cols, rows, terms);
		if (terms > 0)
		{
			int *rowStart = new int[cols];//���ڴ洢ÿһ�е�һ��Ԫ�صĿ�ʼλ��

			fill(rowStart, rowStart + cols, 0);//��ʼ��Ϊ0
			for (int i = 0; i < terms; i++)
				rowStart[smArray[i].col]++;//����ÿһ��nonzeroԪ�ظ���

			int temp1 = rowStart[0]; //����˳�����ÿһ��rowStart��ֵ
			int temp2 = 0;  //����˳�����ÿһ��rowStart��ֵ
			rowStart[0] = 0; //��һ�еĵ�һ��Ԫ�ؿ�ʼ��λ��Ϊ0
			for (int i = 1; i < cols; i++)
			{
				temp2 = temp1;//��temp1��temp2
				temp1 = rowStart[i];//temp1ȡ����ǰ��rowStart��Ϊ��һ�μ���׼��
				rowStart[i] = rowStart[i - 1] + temp2;//ÿһ�еĿ�ʼλ�ã���һ�еĿ�ʼλ��+��һ�е�Ԫ������
			}

			for (int i = 0; i < terms; i++)
			{
				int j = rowStart[smArray[i].col];//�ҳ���Ԫ��ת�ú������еĿ�ʼλ��
				b.smArray[j].row = smArray[i].col;//��ֵ
				b.smArray[j].col = smArray[i].row;//��ֵ
				b.smArray[j].value = smArray[i].value;//��ֵ
				rowStart[smArray[i].col]++;//���п�ʼλ�ü�1��Ϊ��һ��Ԫ��ָ��ռ�
			}
			delete[] rowStart;
		}
		return b;
	}
private:
	int rows, cols, terms, capacity;
	MatrixTerm *smArray;
};

int main()
{
	SparseMatrix a(3, 3, 9);
	int r, c, v;
	cin >> r >> c >> v;
	while (r != -1)
	{
		a.inputElements(r - 1, c - 1, v);
		cin >> r >> c >> v;
	}
	cout << "Initial matrix is:" << endl;
	a.outputMatrix();
	SparseMatrix b = a.FastTranspose();
	cout << "After transpose is:" << endl;
	b.outputMatrix();
	system("pause");
}

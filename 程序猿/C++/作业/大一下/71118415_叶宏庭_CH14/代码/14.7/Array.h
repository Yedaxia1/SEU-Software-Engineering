# ifndef ARRAY_H
# define ARRAY_H

# include <iostream>
# include <iomanip>
# include <cstdlib>
using namespace std;

template<typename T>
class Array {
	friend ostream &operator<<(ostream &output, const Array<T> &a)
	{
		int i;

		for (i = 0; i < a.size; ++i)
		{
			output << setw(12) << a.ptr[i];

			if ((i + 1) % 4 == 0)
				output << endl;
		}

		if (i % 4 != 0)
			output << endl;

		return output;
	}
	friend istream &operator>>(istream &input, Array<T> &a)
	{
		for (int i = 0; i < a.size; ++i)
			input >> a.ptr[i];

		return input;
	}
public:
	Array(int = 10);
	Array(const Array &);
	~Array();
	int getSize() const;

	const Array &operator=(const Array &);
	bool operator==(const Array &) const;

	bool operator!=(const Array &right) const
	{
		return !(*this == right);
	}
	T &operator[](int);

	T operator[](int) const;
private:
	int size;
	T *ptr;
};



template<typename T>
Array<T>::Array(int arraySize)
{
	if (arraySize > 0)
		size = arraySize;
	else
		throw invalid_argument("Array size must be greater than 0");

	ptr = new T[size];

	for (int i = 0; i < size; ++i)
		ptr[i] = 0;
}

template<typename T>
Array<T>::Array(const Array &arrayToCopy)
	:size(arrayToCopy.size)
{
	ptr = new T[size];

	for (int i = 0; i < size; ++i)
		ptr[i] = arrayToCopy.ptr[i];
}

template<typename T>
Array<T>::~Array()
{
	delete[] ptr;
}

template<typename T>
int Array<T>::getSize() const
{
	return size;
}

template<typename T>
const Array<T> &Array<T>::operator=(const Array &right)
{
	if (&right != this)
	{
		if (size != right.size)
		{
			delete[] ptr;
			size = right.size;
			ptr = new T[size];
		}

		for (int i = 0; i < size; ++i)
			ptr[i] = right.ptr[i];
	}

	return *this;
}

template<typename T>
bool Array<T>::operator==(const Array &right) const
{
	if (size != right.size)
		return false;

	for (int i = 0; i < size; ++i)
		if (ptr[i] != right.ptr[i])
			return false;

	return true;
}

template<typename T>
T &Array<T>::operator[](int subscript)
{
	if (subscript < 0 || subscript >= size)
		throw out_of_range("Subscript out of range");

	return ptr[subscript];
}

template<typename T>
T Array<T>::operator[](int subscript) const
{
	if (subscript < 0 || subscript >= size)
		throw out_of_range("Subscript out of range");

	return ptr[subscript];
}

#endif
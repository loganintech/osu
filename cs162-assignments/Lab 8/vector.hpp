#include <stdlib.h>
#include <stdexcept>

using std::exception;
using std::out_of_range;

template <class T>
class vector
{
  private:
	T *v;
	int s;

  public:
	vector()
	{
		s = 0;
		v = NULL;
	}

	vector(vector<T> &other)
	{
		v = NULL;
		for (int i = 0; i < other.s; i++)
		{
			push_back(other.v[i]);
		}
	}

	void operator=(vector<T> &other)
	{
		v = NULL;
		for (int i = 0; i < other.s; i++)
		{
			push_back(other.v[i]);
		}
	}

	~vector()
	{
		delete[] v;
	}

	int size()
	{
		return s;
	}

	void push_back(T ele)
	{
		T *temp;
		temp = new T[s + 1];
		for (int i = 0; i < s; i++)
			temp[i] = v[i];

		delete[] v;
		v = temp;
		v[s++] = ele;
	}

	T operator[](int i)
	{
		return *(v + (i * sizeof(T)));
	}

	T at(int i)
	{
		if (i >= s)
		{
			throw out_of_range("Index is out of range.");
		}
		return *(v + (i * sizeof(T)));

		// try
		// {
		// 	return *(v + (i * sizeof(T)));
		// }
		// catch (exception &e)
		// {
		// 	throw out_of_range(e.what());
		// }
	}
};
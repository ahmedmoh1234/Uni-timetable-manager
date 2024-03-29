#pragma once

template <class T>
class DynArr // all functions are tested and working
{
private:
	int size;
	int capacity;
	T* darr;
public:


	DynArr()
	{
		capacity = 2;
		darr = new T[capacity];
		size = 0;
	}


	T Get(int index) const
	{
		if ( index < 0 || index >= size)
		{
			//throw;
		}
		else
			return darr[index];
	}		

	bool Set(int index, T val)
	{
		if ( index < 0 || index >= size)
		{
			return false;
		}
		else
		{
			darr[index] = val;
			return true;
		}
	}

	bool PushBack(const T& val)
	{
		if ( size == capacity )
		{
			T* arr_new = new T [2 * capacity];
			for ( int  i = 0; i < size ; i++)
			{
				arr_new[i] = darr[i];
			}

			//delete [] darr;
			darr = arr_new;
			capacity = capacity * 2;
		}

		darr[size] = val;
		size++;
		return true;
	}

	bool Remove(int index)
	{
		if ( index < 0 || index >= this->size)
		{
			return false;
		}
		else
		{
			if (index == this->size - 1)
			{
				//darr[index] = nullptr;
				this->size--;
				return true;
			}
			for (int i = index; i <= this->size - 2; i++)
				darr[i] = darr[i+1];
			this->size--;
			return true;
		}

	}

	int Size() const
	{
		return size;
	}

	void Print()
	{
		std::cout << "Printing array started \n";
		for (int i = 0; i < size; i++)
		{
			std::cout << darr[i] << " ";
		}
		std::cout << "Printing array ended \n";
	}

	void PrintPtr()
	{
		std::cout << "Printing array started \n";
		for (int i = 0; i < size; i++)
		{
			std::cout << *(darr[i]) << " ";
		}
		std::cout << "Printing array ended \n";
	}

	template<class T>
	friend ostream & operator << (ostream &out, const DynArr<T> &c);

	template<class T>
	friend ostream & operator << (ostream &out, const DynArr<T*> &c);
	
	~DynArr()
	{
		//delete [] darr;
		//darr = nullptr;
	}


};

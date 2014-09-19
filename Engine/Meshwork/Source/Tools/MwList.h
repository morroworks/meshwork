#pragma once

#include "..\MwGlobals.h"

#include "MwMem.h"

template <typename T> class MwList
{
public:
	static const int ListIndex_NotFound = -1;

	int count, capacity;
	T *values;

	T& operator [](int index) 
	{ 
		return this->values[index]; 
	};

	// Creates a list with the capacity to hold the given number of elements without allocating new memory
	MwList(int capacity = 64)
	{
		this->capacity = 0;
		this->count = 0;
		this->values = 0;

		this->SetCapacity(capacity);
	};

	MwList(T *values, int numValues)
	{
		this->capacity = 0;
		this->count = 0;
		this->values = 0;

		this->SetSize(numValues);

		for (int i = 0; i < numValues; i++)
			this->values[i] = values[i];
	};

	virtual ~MwList(void)
	{
		if (this->values != 0)
			delete[] this->values;
	};

	// Gets the value at the given index	
	T& Get(int index) 
	{ 
		return this->values[index]; 
	};

	// Sets the value at the given index	
	void Set(int index, T value) 
	{ 
		this->values[index] = value;
	};

	// Returns the number of elements in the list
	int Size()
	{
		return this->count;
	}

	// Sets such a capacity of the list, so that it will be able to hold the given number of elements without allocating new memory
	void SetCapacity(int newCapacity)
	{
		T *newValues = newCapacity > 0 ? new T[newCapacity] : 0;
	
		int count = this->count < newCapacity ? this->count : newCapacity;
		for (int i = 0; i < count; i++)
			newValues[i] = this->values[i];

		if (this->values != 0)
			delete[] this->values;

		this->values = newValues;
		this->capacity = newCapacity;
	};

	// If necessary, sets such a capacity of the list, so that it will be able to hold at least the given number of elements without allocating new memory
	void EnsureCapacity(int capacity)
	{
		int newCapacity = this->capacity > 0 ? this->capacity : 1;
		while (capacity > newCapacity)
		{
			newCapacity *= 2;
		}

		if (newCapacity > this->capacity)
		{
			this->SetCapacity(newCapacity);
		}	
	};

	// Sets the size of the list to the number of elements
	void SetSize(int numElements)
	{
		this->EnsureCapacity(numElements);
		this->count = numElements;
	}

	// Clears the list. This method only sets the elements counter to 0, without actually erasing anything, but further insertion operations will put new elements in place of the old ones.
	void Clear()
	{
		this->count = 0;
	}

	// Adds an element with the given value to the end of the list
	T& Add(T value)
	{
		this->EnsureCapacity(this->count + 1);

		this->values[this->count] = value;

		return this->values[this->count++];
	};

	// Inserts an element with the given value at the specified index of the list
	T& Insert(int index, T value)
	{
		this->EnsureCapacity(this->count + 1);

		for (int i = this->count; i > index; i--)
			this->values[i] = this->values[i - 1];

		this->values[index] = value;

		this->count++;

		return this->values[index];
	};

	// Moves elements from their original position and inserts them on a new position, shifting the elements between
	void Move(int originalIndex, int newIndex, int count)
	{
		if ((count <= 0) || (originalIndex == newIndex))
			return;

		T *temp = new T[count];
		MwMem::Copy(temp, &this->values[originalIndex], count * sizeof(T));

		if (originalIndex < newIndex)
		{
			for (int i = originalIndex; i < newIndex; i++)
				this->values[i] = this->values[i + count];
		}
		else
		{
			for (int i = originalIndex - 1; i >= newIndex; i--)
				this->values[i + count] = this->values[i];
		}

		MwMem::Copy(&this->values[newIndex], temp, count * sizeof(T));
		delete[] temp;
	};

	// Removes the first encountered element of the given value. Returns true if an element was removed or false otherwise
	bool Remove(T value)
	{
		int index = this->IndexOf(value);
		if (index != MwList::ListIndex_NotFound)
		{
			this->RemoveAt(index);
			return true;
		}

		return false;
	};

	// Removes all elements of the given value. Returns the number of elements removed
	int RemoveAll(T value)
	{
		int numRemoved = 0;
		int index = this->IndexOf(value);
		while (index != MwList::ListIndex_NotFound)
		{
			this->RemoveAt(index);
			numRemoved++;

			index = this->IndexOf(value);
		}

		return numRemoved;
	};

	// Removes the element at the given index
	void RemoveAt(int index)
	{
		for (int i = index; i < this->count -1; i++)
			this->values[i] = this->values[i + 1];
		this->count--;
	};

	// Removes a number of consequent items from the list, starting from the given index
	void RemoveRange(int index, int count)
	{
		for (int i = index; i < this->count - count; i++)
			this->values[i] = this->values[i + count];
		this->count -= count;
	};

	// Returns the index of the first encountered item of the given value. If such item is not present, the return value is -MwList::ListIndex_NotFound
	int IndexOf(T value)
	{
		for (int i = 0; i < this->count; i++)
			if (MwMem::Compare(&this->values[i], &value, sizeof(T)) == 0)
				return i;

		return MwList::ListIndex_NotFound;
	};
};
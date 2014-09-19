#pragma once

#include "..\MwGlobals.h"

#include "MwLinkedList.h"

template <typename TKey, typename TValue> struct DictionaryEntry
{
	TKey key;
	TValue value;
};


template <typename TKey, typename TValue> class MwDictionary
	: public MwLinkedList<DictionaryEntry<TKey, TValue>>
{
private:
	bool FindEntryNode(TKey key, void *&node)
	{
		for (node = this->GetNodeNext(0); node != 0; node = this->GetNodeNext(node))
		{
			DictionaryEntry<TKey, TValue> entry = this->GetNodeValue(node);
			if (entry.key == key)
				return true;

			if (entry.key > key)
				return false;
		}

		return false;
	};

public:
	MwDictionary(void)
		: MwLinkedList<DictionaryEntry<TKey, TValue>>()
	{
	};

	virtual ~MwDictionary(void)
	{
	};

	// Adds a value with the given key. If the key already exists, the method returns false, true otherwise
	bool Add(TKey key, TValue value)
	{
		void *nextBiggest;
		if (this->FindEntryNode(key, nextBiggest))
			return false;

		DictionaryEntry<TKey, TValue> entry;
		entry.key = key;
		entry.value = value;
		if (nextBiggest != 0)
			this->InsertBefore(nextBiggest, entry);
		else
			this->InsertAfter(this->last, entry);

		return true;
	};

	// Sets a value with the give key. If the key already exists, it refreshes its value with the provided one and returns false. Otherwise it adds the new key with the value and returns true
	bool Set(TKey key, TValue value)
	{
		void *node;
		if (this->FindEntryNode(key, node))
		{
			DictionaryEntry<TKey, TValue> entry;
			entry.key = key;
			entry.value = value;

			this->SetNodeValue(node, entry);
			return false;
		}

		DictionaryEntry<TKey, TValue> entry;
		entry.key = key;
		entry.value = value;
		if (node != 0)
			this->InsertBefore(node, entry);
		else
			this->InsertAfter(this->last, entry);

		return true;
	};

	// Removes the given key with its value. Returns true if the given key was existing and was removed, false if the key didn't exist
	bool Remove(TKey key)
	{
		void *entry;
		if (!this->FindEntryNode(key, entry))
			return false;

		this->RemoveNode(entry);

		return true;
	};

	bool GetValue(TKey key, TValue &value)
	{
		void *entry;
		if (!this->FindEntryNode(key, entry))
			return false;

		value = this->GetNodeValue(entry).value;

		return true;
	};

	bool KeyExists(TKey key)
	{
		void *entry;
		return this->FindEntryNode(key, entry);
	};

	bool ValueExists(TValue value)
	{
		for (void *entry = this->GetNodeNext(0); entry != 0; entry = this->GetNodeNext(entry))
		{
			if (this->GetNodeValue(entry).value == value)
				return true;
		}

		return false;
	};
};
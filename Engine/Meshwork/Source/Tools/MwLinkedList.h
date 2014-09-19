#pragma once

#include "..\MwGlobals.h"

#include "MwMem.h"

template <typename T> class MwLinkedListNode
{
public:
	MwLinkedListNode *previous, *next;
	T value;
};

template <typename T> class MwLinkedList
{
public:
	MwLinkedListNode<T> *last, *first;
	int count;

	MwLinkedList(void)
	{
		this->first = 0;
		this->last = 0;

		this->count = 0;
	};

	virtual ~MwLinkedList(void)
	{
		this->Clear();
	};
	
	void Add(T value)
	{
		this->InsertAfter(this->last, value);
	};

	bool IsEmpty()
	{
		return this->last == 0;
	}

	void Clear()
	{
		while (this->last != 0)
			this->RemoveNode(this->last);
	}

	void *FindFirst(T value)
	{
		MwLinkedListNode<T> *node = first;

		while (node != 0)
		{
			if (MwMem::Compare(&node->value, &value, sizeof(T)) == 0)
				return node;

			node = node->next;
		}

		return 0;
	};

	void *FindLast(T value)
	{
		MwLinkedListNode<T> *node = last;

		while (node != 0)
		{
			if (MwMem::Compare(&node->value, &value, sizeof(T)) == 0)
				return node;

			node = node->previous;
		}

		return 0;
	};

	virtual void InsertBefore(void *node, T value)
	{
		MwLinkedListNode<T> *listNode = (MwLinkedListNode<T>*) node;
		
		MwLinkedListNode<T> *newNode = new MwLinkedListNode<T>();
		newNode->value = value;

		newNode->next = listNode;
		if (listNode != 0)
		{
			newNode->previous = listNode->previous;
			if (listNode->previous != 0)
				listNode->previous->next = newNode;
			else
				this->first = newNode;
			listNode->previous = newNode;
		}
		else
		{
			newNode->previous = 0;
			this->last = newNode;
			this->first = newNode;
		}

		this->count++;
	}

	virtual void InsertAfter(void *node, T value)
	{
		MwLinkedListNode<T> *listNode = (MwLinkedListNode<T>*) node;
		
		MwLinkedListNode<T> *newNode = new MwLinkedListNode<T>();
		newNode->value = value;

		newNode->previous = listNode;
		if (listNode != 0)
		{
			newNode->next = listNode->next;
			if (listNode->next != 0)
				listNode->next->previous = newNode;
			else
				this->last = newNode;
			listNode->next = newNode;
		}
		else
		{
			newNode->next = 0;
			this->last = newNode;
			this->first = newNode;
		}

		this->count++;
	}

	virtual void RemoveNode(void *node)
	{
		MwLinkedListNode<T> *listNode = (MwLinkedListNode<T>*) node;
		
		if (listNode->previous != 0)
			listNode->previous->next = listNode->next;
		else
			this->first = listNode->next;

		if (listNode->next != 0)
			listNode->next->previous = listNode->previous;
		else
			this->last = listNode->previous;

		delete listNode;

		this->count--;
	}

	void *GetNodeNext(void *node)
	{
		if (node != 0)
			return ((MwLinkedListNode<T>*)node)->next;
		else
			return this->first;
	}

	void *GetNodePrevious(void *node)
	{
		if (node != 0)
			return ((MwLinkedListNode<T>*)node)->previous;
		else
			return this->last;
	}

	T &GetNodeValue(void *node)
	{
		return ((MwLinkedListNode<T>*)node)->value;
	}

	void SetNodeValue(void *node, T value)
	{
		((MwLinkedListNode<T>*)node)->value = value;
	}
};
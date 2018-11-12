#pragma once
#include<stdexcept>
template<class T> class MyList{
public:
	MyList()  //���캯��
	{
		pFirst = NULL;
		this->size = 0;
	}

	void Add(const T& t)  //��Link��ͷ����½��
	{
		if (pFirst == NULL)
		{
			pFirst = new Node;
			*(pFirst->pT) = t;
		}
		else
		{
			Node* pNewNode = new Node;
			*(pNewNode->pT) = t;
			pNewNode->pNext = pFirst;
			pFirst = pNewNode;
		}
		this->size++;
	}

	void Remove(T& t) //��Link��ɾ�������ض�ֵ��Ԫ��
	{
		Node* pNode = pFirst;
		if (*(pNode->pT) == t)
		{
			pFirst = pFirst->pNext;
			delete pNode;
			return;
		}
		while (pNode != NULL)
		{
			Node* pNextNode = pNode->pNext;
			if (pNextNode != NULL)
			{
				if (*(pNextNode->pT) == t)
				{
					pNode->pNext = pNextNode->pNext;
					this->size--;
					delete pNextNode;
					return;
				}
			}
			else
				return;//û����ͬ��

			pNode = pNode->pNext;
		}

	}

	T* Find(T& t)  //���Һ����ض�ֵ�Ľ��
	{
		Node* pNode = pFirst;
		while (pNode != NULL)
		{
			if (*(pNode->pT) == t)
			{
				return pNode->pT;
			}
			pNode = pNode->pNext;
		}
		return NULL;
	}

	T* at(int num) const
	{
		if (num < 0 && num < this->getSize())
		{
			std::out_of_range or("Address array bounds");
			throw or;
		}
		Node* pNode = pFirst;
		for (int i = 0; i < num; i++)
		{
			pNode = pNode->pNext;
		}
		return pNode->pT;
	}

	int getSize() const
	{
		return this->size;
	}

	void PrintList()  // ��ӡ�����������
	{
		if (pFirst == NULL)
		{
			cout << "�б�Ϊ���б�" << endl;
			return;
		}
		Node* pNode = pFirst;
		while (pNode != NULL)
		{
			cout << *(pNode->pT) << endl;
			pNode = pNode->pNext;
		}
	}
	~MyList()
	{
		Node* pNode = pFirst;
		while (pNode != NULL)
		{
			Node* pNextNode = pNode->pNext;
			delete pNode;
			pNode = pNextNode;
		}
		this->size = 0;
	}
protected:
	struct Node{
		Node* pNext;
		T* pT;

		Node()
		{
			pNext = NULL;
			pT = new T;
		}
		~Node()
		{
			delete pT;
		}
	};
	Node *pFirst;        //���׽��ָ�몤
	int size;
};
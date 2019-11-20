#pragma once
#include "Common.h"
#include <vector>


#if 0
template<class T>
struct HBNode
{
	HBNode(const T& data = T())
	: _data(data)
	, _pNext(nullptr)
	{}

	T _data;
	HBNode<T>* _pNext;
};


// T������������͵ģ�char short int long long long
template<class T>
struct T2IntDef
{
	T operator()(const T& data)
	{
		return data;
	}
};

// T���������ͣ���Ҫ�û�����ת���ķ�ʽ
struct String2INT
{
	size_t operator()(const string& s)
	{
		return (size_t)(s.c_str());
	}
};


template<class T, class T2Int = T2IntDef<T>>
class HashBucket;

template<class T, class T2Int = T2IntDef<T>>
struct HBIterator
{
	typedef HBNode<T> Node;
	typedef HBIterator<T, T2Int> Self;
	typedef HashBucket<T, T2Int> HB;
	HBIterator(HB* ht = nullptr, Node* pNode = nullptr)
		: _pNode(pNode)
		, _ht(ht)
	{}

	T& operator*()
	{
		return _pNode->_data;
	}

	T* operator->()
	{
		return (&operator*());
	}

	// �ƶ�
	Self& operator++()
	{
		Next();
		return *this;
	}

	Self operator++(int)
	{
		Self temp(*this);
		Next();
		return temp;
	}

	bool operator!=(const Self& s)const
	{
		return _pNode != s._pNode;
	}

	bool operator==(const Self& s)const
	{
		return _pNode == s._pNode;
	}

	void Next()
	{
		if (_pNode->_pNext)
		{
			_pNode = _pNode->_pNext;
		}
		else
		{
			// _pNode�ǵ�ǰͰ��(������)�����һ���ڵ�
			
			// ��ȡ��һ��Ͱ��Ͱ�� = ���㵱ǰͰ��+1
			size_t bucketNo = _ht->HashFunc(_pNode->_data)+1;
			
			// ����һ���ǿ�Ͱ
			for (; bucketNo < _ht->BucketCount(); ++bucketNo)
			{
				_pNode = _ht->_table[bucketNo];
				if (_pNode)
					return;
			}
		}
	}

	Node* _pNode;
	HB* _ht;  // ��ȡ��һ���ǿ�Ͱʱ��Ҫ�õ�
};


// ���裺��ϣͰ�е�Ԫ��ʱΨһ��
template<class T, class T2Int>
class HashBucket
{
	friend struct HBIterator<T, T2Int>;

	typedef HBNode<T> Node;
	typedef HashBucket<T, T2Int> Self;

public:
	typedef HBIterator<T, T2Int> iterator;

public:
	HashBucket(size_t capacity = 10)
		: _table(GetNextPrime(capacity))
		, _size(0)
	{}

	bool Insert(const T& data)
	{
		// 1. ͨ����ϣ��������data���ڵ�Ͱ��
		size_t bucketNo = HashFunc(data);

		// 2. ����Ԫ���Ƿ���bucketNoͰ��
		//    ���ʣ�����������Ƿ����data�Ľڵ�
		Node* pCur = _table[bucketNo];
		while (pCur)
		{
			if (pCur->_data == data)
				return false;

			pCur = pCur->_pNext;
		}

		// �����½ڵ�
		pCur = new Node(data);
		pCur->_pNext = _table[bucketNo];
		_table[bucketNo] = pCur;
		++_size;
		return true;
	}

	Node* Find(const T& data)
	{
		size_t bucketNo = HashFunc(data);
		Node* pCur = _table[bucketNo];
		while (pCur)
		{
			if (data == pCur->_data)
				return pCur;

			pCur = pCur->_pNext;
		}

		return nullptr;
	}

	bool Erase(const T& data)
	{
		size_t bucketNo = HashFunc(data);
		Node* pCur = _table[bucketNo];
		Node* pPre = nullptr;

		while (pCur)
		{
			if (data == pCur->_data)
			{
				// ɾ��
				if (_table[bucketNo] == pCur)
				{
					// ɾ����һ���ڵ�
					_table[bucketNo] = pCur->_pNext;
				}
				else
				{
					// ɾ���Ĳ��ǵ�һ���ڵ�
					pPre->_pNext = pCur->_pNext;
				}

				delete pCur;
				--_size;
				return true;
			}

			pPre = pCur;
			pCur = pCur->_pNext;
		}

		return false;
	}

	iterator Begin()
	{
		// �ҵ�һ���ǿ�Ͱ
		for (size_t i = 0; i < _table.capacity(); ++i)
		{
			if (_table[i])
				return iterator(this, _table[i]);

		}

		return End();
	}

	iterator End()
	{
		return iterator(this, nullptr);
	}

	void Swap(Self& ht)
	{
		_table.swap(ht._table);
		swap(_size, ht._size);
	}

	size_t BucketCount()const
	{
		return _table.capacity();
	}

	void CheckCapacity()
	{
		if (_size == _table.capacity())
		{
#if 0
			HashBucket<T> ht(_size*2);

			// ���ɹ�ϣͰ�е�Ԫ�����¹�ϣͰ�н��а���
			// �������оɹ�ϣͰ�е�Ԫ��
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				Node* pCur = _table[i];
				while (pCur)
				{
					ht.Insert(pCur->_data); // new �ڵ�
					pCur = pCur->_pNext;
				}
			}

			Swap(ht);
#endif
			Self ht(GetNextPrime(_size));

			// ���ɹ�ϣͰ�еĽڵ�ֱ�����¹�ϣͰ�а���
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				Node* pCur = _table[i];
				while (pCur)
				{
					// ��pCur�ڵ�Ӿɹ�ϣͰ���Ƶ��¹�ϣͰ
					// 1. ��pCur�ڵ�Ӿ�������ɾ��
					_table[i] = pCur->_pNext;

					// 2. ��pCur�ڵ���뵽��������
					size_t bucketNo = ht.HashFunc(pCur->_data);

					// 3. ����ڵ�--->ͷ��
					pCur->_pNext = ht._table[bucketNo];
					ht._table[bucketNo] = pCur;
				}
			}

			this->Swap(ht);
		}
	}

	void PrintHashBucket()
	{
		for (size_t i = 0; i < _table.capacity(); ++i)
		{
			cout << "_table[" << i << "]:";

			Node* pCur = _table[i];
			while (pCur)
			{
				cout << pCur->_data << "--->";
				pCur = pCur->_pNext;
			}

			cout << "NULL" << endl;
		}
		cout << endl;
	}

private:
	size_t HashFunc(const T& data)
	{
		return T2Int()(data) % _table.capacity();
	}

private:
	vector<Node*> _table;
	size_t _size;
};


void TestHashBucket1()
{
	HashBucket<int> ht;
	ht.Insert(1);
	ht.Insert(54);
	ht.Insert(2);
	ht.Insert(3);
	ht.Insert(4);
	ht.Insert(5);


	if (ht.Find(3))
		cout << "3 is in hashBucket" << endl;
	else
		cout << "3 is not in hashbucket" << endl;

	ht.PrintHashBucket();
	HashBucket<int>::iterator it = ht.Begin();
	while (it != ht.End())
	{
		cout << *it << " ";
		++it;
	}

	cout << endl;
}

#include <string>
void TestHashBucket2()
{
	HashBucket<string, String2INT> ht;
	ht.Insert("1111");
	ht.Insert("2222");
	ht.Insert("3333");
	ht.Insert("4444");
	ht.Insert("5555");
}
#endif

template<class T>
struct HBNode
{
	HBNode(const T& data = T())
	: _data(data)
	, _pNext(nullptr)
	{}

	T _data;
	HBNode<T>* _pNext;
};


// T������������͵ģ�char short int long long long
template<class T>
struct T2IntDef
{
	T operator()(const T& data)
	{
		return data;
	}
};

// T���������ͣ���Ҫ�û�����ת���ķ�ʽ
struct String2INT
{
	size_t operator()(const string& s)
	{
		const char* str = s.c_str();
		unsigned int seed = 131; // 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}
};


template<class T, class KOFV, class T2Int = T2IntDef<T>>
class HashBucket;

template<class T, class KOFV, class T2Int = T2IntDef<T>>
struct HBIterator
{
	typedef HBNode<T> Node;
	typedef HBIterator<T, KOFV, T2Int> Self;
	typedef HashBucket<T, KOFV, T2Int> HB;
	HBIterator(HB* ht = nullptr, Node* pNode = nullptr)
		: _pNode(pNode)
		, _ht(ht)
	{}

	T& operator*()
	{
		return _pNode->_data;
	}

	T* operator->()
	{
		return (&operator*());
	}

	// �ƶ�
	Self& operator++()
	{
		Next();
		return *this;
	}

	Self operator++(int)
	{
		Self temp(*this);
		Next();
		return temp;
	}

	bool operator!=(const Self& s)const
	{
		return _pNode != s._pNode;
	}

	bool operator==(const Self& s)const
	{
		return _pNode == s._pNode;
	}

	void Next()
	{
		if (_pNode->_pNext)
		{
			_pNode = _pNode->_pNext;
		}
		else
		{
			// _pNode�ǵ�ǰͰ��(������)�����һ���ڵ�

			// ��ȡ��һ��Ͱ��Ͱ�� = ���㵱ǰͰ��+1
			size_t bucketNo = _ht->HashFunc(_pNode->_data) + 1;

			// ����һ���ǿ�Ͱ
			for (; bucketNo < _ht->BucketCount(); ++bucketNo)
			{
				_pNode = _ht->_table[bucketNo];
				if (_pNode)
					return;
			}

			_pNode = nullptr;
		}
	}

	Node* _pNode;
	HB* _ht;  // ��ȡ��һ���ǿ�Ͱʱ��Ҫ�õ�
};


// ���裺��ϣͰ�е�Ԫ��ʱΨһ��
template<class T, class KOFV, class T2Int>
class HashBucket
{
	friend struct HBIterator<T, KOFV, T2Int>;

	typedef HBNode<T> Node;
	typedef HashBucket<T, KOFV, T2Int> Self;

public:
	typedef HBIterator<T, KOFV, T2Int> iterator;

public:
	HashBucket(size_t capacity = 10)
		: _table(GetNextPrime(capacity))
		, _size(0)
	{}

	/////////////////////////////////////
	// capacity
	size_t Size()const
	{
		return _size;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	pair<iterator, bool> Insert(const T& data)
	{
		// 1. ͨ����ϣ��������data���ڵ�Ͱ��
		size_t bucketNo = HashFunc(data);

		// 2. ����Ԫ���Ƿ���bucketNoͰ��
		//    ���ʣ�����������Ƿ����data�Ľڵ�
		Node* pCur = _table[bucketNo];
		while (pCur)
		{
			if (pCur->_data == data)
				return make_pair(iterator(this, pCur), false);

			pCur = pCur->_pNext;
		}

		// �����½ڵ�
		pCur = new Node(data);
		pCur->_pNext = _table[bucketNo];
		_table[bucketNo] = pCur;
		++_size;
		return make_pair(iterator(this, pCur), true);
	}

	size_t Erase(const T& data)
	{
		size_t bucketNo = HashFunc(data);
		Node* pCur = _table[bucketNo];
		Node* pPre = nullptr;

		while (pCur)
		{
			if (data == pCur->_data)
			{
				// ɾ��
				if (_table[bucketNo] == pCur)
				{
					// ɾ����һ���ڵ�
					_table[bucketNo] = pCur->_pNext;
				}
				else
				{
					// ɾ���Ĳ��ǵ�һ���ڵ�
					pPre->_pNext = pCur->_pNext;
				}

				delete pCur;
				--_size;
				return 1;
			}

			pPre = pCur;
			pCur = pCur->_pNext;
		}

		return 0;
	}

	void Clear()
	{
		for (size_t i = 0; i < _table.capacity(); ++i)
		{
			Node* pCur = _table[i];

			// ɾ��i��Ͱ����Ӧ�����е����нڵ�
			while (pCur)
			{
				// ����ͷɾ
				_table[i] = pCur->_pNext;
				delete pCur;
				pCur = _table[i];
			}
		}

		_size = 0;
	}

	void Swap(Self& ht)
	{
		_table.swap(ht._table);
		swap(_size, ht._size);
	}

	/////////////////////////////////////

	iterator Find(const T& data)
	{
		size_t bucketNo = HashFunc(data);
		Node* pCur = _table[bucketNo];
		while (pCur)
		{
			if (data == pCur->_data)
				return iterator(this, pCur);

			pCur = pCur->_pNext;
		}

		return End();
	}

	/////////////////////////////////////////
	iterator Begin()
	{
		// �ҵ�һ���ǿ�Ͱ
		for (size_t i = 0; i < _table.capacity(); ++i)
		{
			if (_table[i])
				return iterator(this, _table[i]);

		}

		return End();
	}

	iterator End()
	{
		return iterator(this, nullptr);
	}

	size_t BucketCount()const
	{
		return _table.capacity();
	}

	size_t BucketSize(size_t n)const
	{
		assert(n < _table.capacity());
		Node* pCur = _table[n];

		size_t count = 0;
		while (pCur)
		{
			count++;
			pCur = pCur->_pNext;
		}

		return count;
	}

	size_t Bucket(const T& data)const
	{
		return HashFunc(data);
	}


private:
	void CheckCapacity()
	{
		if (_size == _table.capacity())
		{
			Self ht(GetNextPrime(_size));

			// ���ɹ�ϣͰ�еĽڵ�ֱ�����¹�ϣͰ�а���
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				Node* pCur = _table[i];
				while (pCur)
				{
					// ��pCur�ڵ�Ӿɹ�ϣͰ���Ƶ��¹�ϣͰ
					// 1. ��pCur�ڵ�Ӿ�������ɾ��
					_table[i] = pCur->_pNext;

					// 2. ��pCur�ڵ���뵽��������
					size_t bucketNo = ht.HashFunc(pCur->_data);

					// 3. ����ڵ�--->ͷ��
					pCur->_pNext = ht._table[bucketNo];
					ht._table[bucketNo] = pCur;
				}
			}

			this->Swap(ht);
		}
	}

private:
	size_t HashFunc(const T& data)
	{
		return T2Int()(KOFV()(data)) % _table.capacity();
	}

private:
	vector<Node*> _table;
	size_t _size;
};


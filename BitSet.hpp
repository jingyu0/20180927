#pragma once

#include <vector>
namespace bite
{
	// N ����
	class bite
	{
	public:
		bite(size_t totalBit)
			: _bst((totalBit>>3)+1)
			, _size(0)
		{}

		// ����which������λ��1
		void set(size_t which)
		{
			if (which < _totalBite)
				return;

			size_t index = (which >> 3);
			size_t pos = which % 8;

			_bst[index] |= (1 << pos);
			++_size;
		}

		// ����which��������0
		void reset(size_t which)
		{
			if (which < _totalBite)
				return;

			size_t index = (which >> 3);
			size_t pos = which % 8;

			_bst[index] &= (~(1 << pos));
			--_size;
		}

		// ���which��Ӧ�ı���λ�Ƿ�Ϊ1
		bool test(size_t which)
		{
			if (which < _totalBite)
				return;

			size_t index = (which >> 3);
			size_t pos = which % 8;

			return  _bst[index] & (1 << pos);
		}

		size_t size()const
		{
			return _totalBite;
		}

		// ����Ϊ1�ı���λ����
		size_t count()const
		{
			return _size;
		}

	private:
		std::vector<unsigned char> _bst;
		size_t _size;  // Ϊ1�ı���λ�ĸ��� --- ���û��_size�ĳ�Ա����ο��ٷ���bitset��Ϊ1�ı���λ�ܵĸ�����
		size_t _totalBite;  // �ܵı���Ϊ����
	};
}

#pragma once

#include "RE/N/NiTCollection.h"

namespace RE
{
	template <class T, class Allocator>
	class NiTSet
	{
	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::uint32_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = T*;
		using const_iterator = const T*;

		NiTSet(std::uint32_t a_initialSize = 0) :
			_data(0),
			_capacity(a_initialSize),
			_size(0)
		{
			if (_capacity > 0) {
				_data = allocator_type::Allocate(_capacity);
			}
		}

		~NiTSet()
		{
			allocator_type::Deallocate(_data);
		}

		reference operator[](size_type a_pos)
		{
			assert(a_pos < size());
			return _data[a_pos];
		}

		const_reference operator[](size_type a_pos) const
		{
			assert(a_pos < size());
			return _data[a_pos];
		}

		reference front()
		{
			return operator[](0);
		}

		[[nodiscard]] const_reference front() const
		{
			return operator[](0);
		}

		reference back()
		{
			return operator[](size() - 1);
		}

		[[nodiscard]] const_reference back() const
		{
			return operator[](size() - 1);
		}

		iterator begin()
		{
			return _data;
		}

		[[nodiscard]] const_iterator begin() const
		{
			return _data;
		}

		[[nodiscard]] const_iterator cbegin() const
		{
			return _data;
		}

		iterator end()
		{
			return _data + _size;
		}

		[[nodiscard]] const_iterator end() const
		{
			return _data + _size;
		}

		[[nodiscard]] const_iterator cend() const
		{
			return _data + _size;
		}

		[[nodiscard]] bool empty() const
		{
			return _capacity == 0;
		}

		[[nodiscard]] size_type size() const
		{
			return _size;
		}

		[[nodiscard]] size_type capacity() const
		{
			return _capacity;
		}

	private:
		T*            _data;      // 00
		std::uint32_t _capacity;  // 08
		std::uint32_t _size;      // 0C
	};
	static_assert(sizeof(NiTSet<void*, NiTMallocInterface<void*>>) == 0x10);

	template <class T>
	class NiTObjectSet : public NiTSet<T, NiTNewInterface<T>>
	{
	public:
		NiTObjectSet(std::uint32_t a_initialSize = 0) :
			NiTSet<T, NiTNewInterface<T>>(a_initialSize)
		{}
	};
	static_assert(sizeof(NiTObjectSet<void*>) == 0x10);

	template <class T>
	class NiTPrimitiveSet : public NiTSet<T, NiTMallocInterface<T>>
	{
	public:
		NiTPrimitiveSet(std::uint32_t a_initialSize = 0) :
			NiTSet<T, NiTMallocInterface<T>>(a_initialSize)
		{}
	};
	static_assert(sizeof(NiTPrimitiveSet<void*>) == 0x10);
}

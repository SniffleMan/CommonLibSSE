#pragma once

#include "RE/M/MemoryManager.h"

namespace RE
{
	template <class Key, class T>
	class NiTMapItem
	{
	public:
		using key_type = Key;
		using mapped_type = T;

		// members
		NiTMapItem* next;    // 00
		key_type    first;   // 08
		mapped_type second;  // ??
	};
	static_assert(sizeof(NiTMapItem<std::uint32_t, std::uint64_t>) == 0x18);

	// hash table with separate chaining
	template <class Allocator, class Key, class T>
	class NiTMapBase
	{
	private:
		template <class U>
		friend class iterator_base;

	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = NiTMapItem<Key, T>;
		using size_type = std::uint32_t;

		template <class U>
		struct iterator_base
		{
		public:
			using difference_type = std::ptrdiff_t;
			using value_type = U;
			using pointer = U*;
			using reference = U&;
			using iterator_category = std::forward_iterator_tag;

			iterator_base() :
				_proxy(0),
				_iter(0),
				_idx(0)
			{}

			iterator_base(const iterator_base& a_rhs) :
				_proxy(a_rhs._proxy),
				_iter(a_rhs._iter),
				_idx(a_rhs._idx)
			{}

			iterator_base(iterator_base&& a_rhs) :
				_proxy(a_rhs._proxy),
				_iter(std::move(a_rhs._iter)),
				_idx(std::move(a_rhs._idx))
			{
				assert(_proxy);
				a_rhs._iter = nullptr;
				a_rhs._idx = a_rhs._proxy->_capacity;
			}

			iterator_base(NiTMapBase* a_proxy, std::uint32_t a_idx) :
				_proxy(a_proxy),
				_iter(nullptr),
				_idx(a_idx)
			{
				assert(_proxy);
				_iter = _proxy->_data[_idx];
				while (!_iter && _idx < _proxy->_capacity) {
					++_idx;
					_iter = _proxy->_data[_idx];
				}
			}

			iterator_base(NiTMapBase* a_proxy, value_type* a_iter, std::uint32_t a_idx) :
				_proxy(a_proxy),
				_iter(a_iter),
				_idx(a_idx)
			{
				assert(_proxy);
				assert(_iter);
			}

			~iterator_base()
			{}

			iterator_base& operator=(const iterator_base& a_rhs)
			{
				assert(_proxy == a_rhs._proxy);
				_iter = a_rhs._iter;
				_idx = a_rhs._idx;
			}

			iterator_base& operator=(iterator_base&& a_rhs)
			{
				assert(_proxy == a_rhs._proxy);

				_iter = std::move(a_rhs._iter);
				a_rhs._iter = 0;

				_idx = std::move(a_rhs._idx);
				a_rhs._idx = a_rhs._proxy->_capacity;
			}

			void swap(iterator_base& a_rhs)
			{
				assert(_proxy == a_rhs._proxy);
				std::swap(_iter, a_rhs._iter);
				std::swap(_idx, a_rhs._idx);
			}

			[[nodiscard]] reference operator*() const
			{
				assert(_iter);
				assert(_idx < _proxy->_capacity);
				return *_iter;
			}

			[[nodiscard]] pointer operator->() const
			{
				assert(_iter);
				assert(_idx < _proxy->_capacity);
				return _iter;
			}

			[[nodiscard]] bool operator==(const iterator_base& a_rhs) const
			{
				assert(_proxy == a_rhs._proxy);

				if (_idx != a_rhs._idx) {
					return false;
				}

				if (_idx < _proxy->_capacity) {
					return _iter == a_rhs._iter;
				}

				return true;
			}

			[[nodiscard]] bool operator!=(const iterator_base& a_rhs) const
			{
				return !operator==(a_rhs);
			}

			// prefix
			iterator_base& operator++()
			{
				assert(_proxy);
				assert(_iter);
				assert(_idx < _proxy->_capacity);

				if (_iter->next) {
					_iter = _iter->next;
				} else {
					do {
						++_idx;
						_iter = _proxy->_data[_idx];
					} while (!_iter && _idx < _proxy->_capacity);
				}

				return *this;
			}

			// postfix
			iterator_base operator++(int)
			{
				iterator_base tmp(*this);
							  operator++();
				return tmp;
			}

		private:
			NiTMapBase*   _proxy;
			value_type*   _iter;
			std::uint32_t _idx;
		};

		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		struct AntiBloatAllocator : public Allocator
		{
			AntiBloatAllocator() :
				Allocator(),
				size(0)
			{}

			// members
			size_type size;  // ??
		};

		NiTMapBase(size_type a_capacity = 37) :
			_capacity(a_capacity),
			_pad0C(0),
			_data(0),
			_allocator()
		{
			std::size_t memSize = sizeof(value_type*) * _capacity;
			_data = malloc<value_type*>(memSize);
			std::memset(_data, 0, memSize);
		}

		virtual ~NiTMapBase()  // 00
		{
			clear();
			if (_data) {
				free(_data);
				_data = nullptr;
			}
			_capacity = 0;
		}

	protected:
		virtual std::uint32_t hash_function(key_type a_key) const;                                      // 01 - { return a_key % _capacity; }
		virtual bool          key_eq(key_type a_lhs, key_type a_rhs) const;                             // 02 - { return stricmp(a_lhs == a_rhs); }
		virtual void          assign_value(value_type* a_value, key_type a_key, mapped_type a_mapped);  // 03 - { a_value->key = a_key; a_value->mapped = a_mapped; }
		virtual void          clear_value(value_type* a_value);                                         // 04 - { return; }
		virtual value_type*   malloc_value() = 0;                                                       // 05
		virtual void          free_value(value_type* a_value) = 0;                                      // 06

	public:
		iterator begin()
		{
			return iterator(this, 0);
		}

		const_iterator begin() const
		{
			return const_iterator(this, 0);
		}

		const_iterator cbegin() const
		{
			return const_iterator(this, 0);
		}

		iterator end()
		{
			return iterator(this, _capacity);
		}

		const_iterator end() const
		{
			return const_iterator(this, _capacity);
		}

		const_iterator cend() const
		{
			return const_iterator(this, _capacity);
		}

		[[nodiscard]] bool empty() const noexcept
		{
			return _allocator.size == 0;
		}

		[[nodiscard]] size_type size() const noexcept
		{
			return _allocator.size;
		}

		void clear()
		{
			for (std::uint32_t i = 0; i < _capacity; i++) {
				while (_data[i]) {
					auto elem = _data[i];
					_data[i] = _data[i]->next;
					clear_value(elem);
					free_value(elem);
				}
			}

			_allocator.size = 0;
		}

		template <class M>
		bool insert_or_assign(key_type&& a_key, M&& a_obj)
		{
			// look up hash table location for key
			auto index = hash_function(a_key);
			auto item = _data[index];

			// search list at hash table location for key
			while (item) {
				if (key_eq(a_key, item->key)) {
					// item already in hash table, set its new value
					item->val = std::forward<M>(a_obj);
					return false;
				}
				item = item->next;
			}

			// add object to beginning of list for this hash table index
			item = malloc_value();

			assert(item != 0);
			assign_value(item, std::move(a_key), std::forward<M>(a_obj));
			item->next = _data[index];
			_data[index] = item;
			++_allocator.size;
			return true;
		}

		size_type erase(const key_type& a_key)
		{
			// look up hash table location for key
			auto index = hash_function(a_key);
			auto item = _data[index];

			value_type* prev = 0;
			while (item) {
				if (key_eq(a_key, item->key)) {
					if (prev) {
						prev->next = item->next;
					} else {
						_data[index] = item->next;
					}
					remove_value(item);
					return 1;
				}
				prev = item;
				item = item->next;
			}
			return 0;
		}

		iterator find(const Key& a_key)
		{
			auto result = do_find(a_key);
			return result ? iterator(this, result->first, result->second) : end();
		}

		const_iterator find(const Key& a_key) const
		{
			auto result = do_find(a_key);
			return result ? const_iterator(this, result->first, result->second) : end();
		}

	private:
		inline void remove_value(value_type* a_value)
		{
			clear_value(a_value);
			free_value(a_value);
			--_allocator.size;
		}

		std::optional<std::pair<value_type*, std::uint32_t>> do_find(const Key& a_key) const
		{
			size_type idx = hash_function(a_key);
			for (auto iter = _data[idx]; iter; iter = iter->next) {
				if (key_eq(a_key, iter->first)) {
					return std::make_optional(std::make_pair(iter, idx));
				}
			}

			return std::nullopt;
		}

	protected:
		// members
		std::uint32_t      _capacity;   // 08
		std::uint32_t      _pad0C;      // 0C
		value_type**       _data;       // 10
		AntiBloatAllocator _allocator;  // 18
	};
}

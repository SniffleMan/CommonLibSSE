#pragma once

namespace RE
{
	template <class T>
	struct GListNode
	{
	public:
		GListNode() :
			prev{ 0 },
			next{ 0 }
		{}

		void Remove()
		{
			prev->next = next;
			next->prev = prev;
		}

		GListNode<T>* prev;  // 00
		GListNode<T>* next;  // 08
	};
	static_assert(sizeof(GListNode<void*>) == 0x10);

	// circular doubly-linked list
	// classes must derive from GListNode
	template <class T>
	class GList
	{
	private:
		using Node = GListNode<T>;

	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = typename std::pointer_traits<pointer>::template rebind<const value_type>;

		template <class U>
		struct iterator_traits
		{
			using difference_type = std::ptrdiff_t;
			using value_type = U;
			using pointer = U*;
			using reference = U&;
			using iterator_category = std::bidirectional_iterator_tag;
		};

		template <class U>
		class iterator_base : public iterator_traits<U>
		{
		private:
			friend class GList<T>;

			using Traits = iterator_traits<U>;

		public:
			using difference_type = typename Traits::difference_type;
			using value_type = typename Traits::value_type;
			using pointer = typename Traits::pointer;
			using reference = typename Traits::reference;
			using iterator_category = typename Traits::iterator_category;

			iterator_base() :
				_cur{ 0 }
			{}

			iterator_base(Node* a_node)
			{
				_cur = a_node;
			}

			iterator_base(const iterator_base& a_rhs) :
				_cur(a_rhs._cur)
			{}

			iterator_base(iterator_base&& a_rhs) :
				_cur(std::move(a_rhs._cur))
			{
				a_rhs._cur = 0;
			}

			static void swap(iterator_base& a_lhs, iterator_base& a_rhs)
			{
				std::swap(a_lhs._cur, a_rhs._cur);
			}

			iterator_base& operator=(const iterator_base& a_rhs)
			{
				iterator_base tmp(a_rhs);
				swap(*this, tmp);
			}

			iterator_base& operator=(iterator_base&& a_rhs)
			{
				_cur = std::move(a_rhs._cur);
				a_rhs._cur = 0;
			}

			[[nodiscard]] reference operator*() const
			{
				return (reference)*_cur;
			}

			[[nodiscard]] pointer operator->() const
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			[[nodiscard]] bool operator==(const iterator_base& a_rhs) const
			{
				return _cur == a_rhs._cur;
			}

			[[nodiscard]] bool operator!=(const iterator_base& a_rhs) const
			{
				return !operator==(a_rhs);
			}

			// prefix
			iterator_base& operator++()
			{
				_cur = _cur->next;
				return *this;
			}

			// postfix
			iterator_base operator++(int)
			{
				iterator_base tmp{ *this };
							  operator++();
				return tmp;
			}

			// prefix
			iterator_base& operator--()
			{
				_cur = _cur->prev;
				return *this;
			}

			// postifx
			iterator_base operator--(int)
			{
				iterator_base tmp{ *this };
							  operator--();
				return tmp;
			}

		protected:
			Node* _cur;
		};

		using iterator = iterator_base<T>;
		using const_iterator = iterator_base<const T>;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		GList() :
			_root{}
		{
			_root.next = _root.prev = &_root;
		}

		reference front()
		{
			return (reference)_root.next;
		}

		[[nodiscard]] const_reference front() const
		{
			return (const_reference)_root.next;
		}

		reference back()
		{
			return (reference)_root.prev;
		}

		[[nodiscard]] const_reference back() const
		{
			return (const_reference)_root.prev;
		}

		iterator begin() noexcept
		{
			return iterator(_root.next);
		}

		[[nodiscard]] const_iterator begin() const noexcept
		{
			return const_iterator(_root.next);
		}

		[[nodiscard]] const_iterator cbegin() const noexcept
		{
			return const_iterator(_root.next);
		}

		iterator end() noexcept
		{
			return iterator(&_root);
		}

		[[nodiscard]] const_iterator end() const noexcept
		{
			return const_iterator(const_cast<GListNode<value_type>*>(&_root));
		}

		[[nodiscard]] const_iterator cend() const noexcept
		{
			return const_iterator(const_cast<GListNode<value_type>*>(&_root));
		}

		reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(_root.prev);
		}

		[[nodiscard]] const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator(_root.prev);
		}

		[[nodiscard]] const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator(_root.prev);
		}

		reverse_iterator rend() noexcept
		{
			return reverse_iterator(&_root);
		}

		[[nodiscard]] const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator(const_cast<GListNode<value_type>*>(&_root));
		}

		[[nodiscard]] const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator(const_cast<GListNode<value_type>*>(&_root));
		}

		[[nodiscard]] bool empty() const noexcept
		{
			return _root.next == &_root;
		}

		[[nodiscard]] size_type size() const noexcept
		{
			size_type size = 0;
			for (auto it = begin(); it != end(); ++it) {
				++size;
			}
			return size;
		}

		void clear() noexcept
		{
			_root.next = _root.prev = &_root;
		}

		iterator insert(const_iterator a_pos, const T& a_value)
		{
			Node* node = (Node*)&a_value;
			node->prev = a_pos._cur->prev;
			a_pos._cur->prev->next = node;
			node->next = a_pos._cur;
			a_pos._cur->prev = node;
			return { node };
		}

		iterator erase(const_iterator a_pos)
		{
			a_pos._cur->prev->next = a_pos._cur->next;
			a_pos._cur->next->prev = a_pos._cur->prev;
		}

		iterator erase(const_iterator a_first, const_iterator a_last)
		{
			a_first._cur->prev->next = a_last._cur->next;
			a_last._cur->next->prev = a_first._cur->prev;
		}

		void push_back(const T& a_value)
		{
			Node* node = (Node*)&a_value;
			node->next = &_root;
			node->prev = _root.prev;
			_root.prev->next = node;
			_root.prev = node;
		}

		void pop_back()
		{
			_root.prev = _root.prev->prev;
			_root.prev->next = &_root;
		}

		void push_front(const T& a_value)
		{
			Node* node = (Node*)&a_value;
			node->next = _root.next;
			node->prev = &_root;
			_root.next->prev = node;
			_root.next = node;
		}

		void pop_front()
		{
			_root.next = _root.next->next;
			_root.next->prev = &_root;
		}

		void merge(GList& a_other)
		{
			while (!a_other.empty()) {
				push_front(a_other.front());
			}
		}

	protected:
		// members
		GListNode<value_type> _root;  // 00
	};
	static_assert(sizeof(GList<void*>) == 0x10);
}

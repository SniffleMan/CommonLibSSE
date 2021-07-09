#pragma once

namespace RE
{
	template <class C, class U, class Hash>
	struct GHashNode
	{
		using SelfType = GHashNode<C, U, Hash>;
		using FirstType = C;
		using SecondType = U;

		struct NodeRef
		{
			const C* first;   // 00
			const U* second;  // 08

			NodeRef(const C& a_first, const U& a_second) :
				first(&a_first),
				second(&a_second)
			{}

			NodeRef(const NodeRef& a_src) :
				first(a_src.first),
				second(a_src.second)
			{}

			[[nodiscard]] inline UPInt GetHash() const
			{
				return Hash()(*first);
			}

			operator const C&() const
			{
				return *first;
			}
		};
		static_assert(sizeof(NodeRef) == 0x10);

		struct NodeHashF
		{
			template <class K>
			UPInt operator()(const K& a_data) const
			{
				return a_data.GetHash();
			}
		};
		static_assert(sizeof(NodeHashF) == 0x1);

		struct NodeAltHashF
		{
			template <class K>
			UPInt operator()(const K& a_data) const
			{
				return GHashNode<C, U, Hash>::CalcHash(a_data);
			}
		};
		static_assert(sizeof(NodeAltHashF) == 0x1);

		GHashNode(const GHashNode& a_src) :
			first(a_src.first),
			second(a_src.second)
		{}

		GHashNode(const NodeRef& a_src) :
			first(*a_src.first),
			second(*a_src.second)
		{}

		void operator=(const NodeRef& a_src)
		{
			first = *a_src.first;
			second = *a_src.second;
		}

		template <class K>
		bool operator==(const K& a_src) const
		{
			return (first == a_src);
		}

		template <class K>
		static UPInt CalcHash(const K& a_data)
		{
			return Hash()(a_data);
		}

		[[nodiscard]] inline UPInt GetHash() const
		{
			return Hash()(first);
		}

		// members
		C first;   // 00
		U second;  // ??
	};
}

#pragma once

#include "RE/G/GAllocator.h"
#include "RE/G/GFixedSizeHash.h"
#include "RE/G/GHashNode.h"
#include "RE/G/GHashSet.h"
#include "RE/G/GHashsetCachedNodeEntry.h"
#include "RE/G/GMemory.h"

namespace RE
{
	template <
		class C,
		class U,
		class HashF = GFixedSizeHash<C>,
		class Allocator = GAllocatorGH<C>,
		class HashNode = GHashNode<C, U, HashF>,
		class Entry = GHashsetCachedNodeEntry<HashNode, typename HashNode::NodeHashF>,
		class Container = GHashSet<HashNode, typename HashNode::NodeHashF, typename HashNode::NodeAltHashF, Allocator, Entry>>
	class GHash
	{
	public:
		using SelfType = GHash<C, U, HashF, Allocator, HashNode, Entry, Container>;
		using const_iterator = typename Container::const_iterator;
		using iterator = typename Container::iterator;

		GHash()
		{}

		GHash(std::int32_t a_sizeHint) :
			hash(a_sizeHint)
		{}

		explicit GHash(void* a_heap) :
			hash(a_heap)
		{}

		GHash(void* a_heap, std::int32_t a_sizeHint) :
			hash(a_heap, a_sizeHint)
		{}

		GHash(const SelfType& a_src) :
			hash(a_src.hash)
		{}

		~GHash()
		{}

		GFC_MEMORY_REDEFINE_NEW(GHash, Allocator::kStatID);

		void operator=(const SelfType& a_src)
		{
			hash = a_src.hash;
		}

		inline void Clear()
		{
			hash.Clear();
		}

		[[nodiscard]] inline bool IsEmpty() const
		{
			return hash.IsEmpty();
		}

		inline void Set(const C& a_key, const U& a_value)
		{
			typename HashNode::NodeRef entry(a_key, a_value);
			hash.Set(entry);
		}

		inline void Add(const C& a_key, const U& a_value)
		{
			typename HashNode::NodeRef entry(a_key, a_value);
			hash.Add(entry);
		}

		inline void Remove(const C& a_key)
		{
			hash.RemoveAlt(a_key);
		}

		template <class K>
		inline void RemoveAlt(const K& a_key)
		{
			hash.RemoveAlt(a_key);
		}

		bool Get(const C& a_key, U* a_value) const
		{
			const HashNode* ptr = hash.GetAlt(a_key);
			if (ptr) {
				if (a_value) {
					*a_value = ptr->second;
				}
				return true;
			}
			return false;
		}

		template <class K>
		bool GetAlt(const K& a_key, U* a_value) const
		{
			const HashNode* ptr = hash.GetAlt(a_key);
			if (ptr) {
				if (a_value) {
					*a_value = ptr->second;
				}
				return true;
			}
			return false;
		}

		inline U* Get(const C& a_key)
		{
			HashNode* ptr = hash.GetAlt(a_key);
			return ptr ? &ptr->second : nullptr;
		}

		inline const U* Get(const C& a_key) const
		{
			const HashNode* ptr = hash.GetAlt(a_key);
			return ptr ? &ptr->second : nullptr;
		}

		template <class K>
		inline U* GetAlt(const K& a_key)
		{
			HashNode* ptr = hash.GetAlt(a_key);
			return ptr ? &ptr->second : nullptr;
		}

		template <class K>
		inline const U* GetAlt(const K& a_key) const
		{
			const HashNode* ptr = hash.GetAlt(a_key);
			return ptr ? &ptr->second : nullptr;
		}

		[[nodiscard]] inline UPInt GetSize() const
		{
			return hash.GetSize();
		}

		inline void Resize(UPInt a_size)
		{
			hash.Resize(a_size);
		}

		inline void SetCapacity(UPInt a_newSize)
		{
			hash.SetCapacity(a_newSize);
		}

		inline iterator begin()
		{
			return hash.begin();
		}

		inline iterator end()
		{
			return hash.end();
		}

		inline const_iterator begin() const
		{
			return hash.begin();
		}

		inline const_iterator end() const
		{
			return hash.end();
		}

		iterator Find(const C& a_key)
		{
			return hash.FindAlt(a_key);
		}

		const_iterator Find(const C& a_key) const
		{
			return hash.FindAlt(a_key);
		}

		template <class K>
		iterator FindAlt(const K& a_key)
		{
			return hash.FindAlt(a_key);
		}

		template <class K>
		const_iterator FindAlt(const K& a_key) const
		{
			return hash.FindAlt(a_key);
		}

		// members
		Container hash;  // 00
	};
}

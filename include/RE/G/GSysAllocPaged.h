#pragma once

#include "RE/G/GSysAllocBase.h"

namespace RE
{
	class GHeapMemVisitor;
	class GHeapSegVisitor;

	class GSysAllocPaged : public GSysAllocBase
	{
	public:
		static constexpr auto RTTI{ RTTI_GSysAllocPaged };

		struct Info
		{
		public:
			// members
			std::size_t minAlign;            // 00
			std::size_t maxAlign;            // 08
			std::size_t granularity;         // 10
			std::size_t sysDirectThreshold;  // 18
			std::size_t maxHeapGranularity;  // 20
			bool        hasRealloc;          // 28
		};
		static_assert(sizeof(Info) == 0x30);

		// override (GSysAllocBase)
		bool InitHeapEngine(const void* a_heapDesc) override  // 01
		{
			using func_t = decltype(&GSysAllocPaged::InitHeapEngine);
			REL::Relocation<func_t> func{ REL::ID(82462) };
			return func(this, a_heapDesc);
		}

		void ShutdownHeapEngine() override  // 02
		{
			using func_t = decltype(&GSysAllocPaged::ShutdownHeapEngine);
			REL::Relocation<func_t> func{ REL::ID(82464) };
			return func(this);
		}

		// add
		virtual void  GetInfo(Info* a_info) const = 0;                                 // 03
		virtual void* Alloc(std::size_t a_size, std::size_t a_align) = 0;              // 04
		virtual bool  Free(void* a_ptr, std::size_t a_size, std::size_t a_align) = 0;  // 05
		virtual bool  ReallocInPlace(
			 [[maybe_unused]] void*       a_oldPtr,
			 [[maybe_unused]] std::size_t a_oldSize,
			 [[maybe_unused]] std::size_t a_newSize,
			 [[maybe_unused]] std::size_t a_align) { return false; }  // 06
		virtual void* AllocSysDirect(
			[[maybe_unused]] std::size_t  a_size,
			[[maybe_unused]] std::size_t  a_alignment,
			[[maybe_unused]] std::size_t* a_actualSize,
			[[maybe_unused]] std::size_t* a_actualAlign) { return nullptr; }  // 07
		virtual bool FreeSysDirect(
			[[maybe_unused]] void*       a_ptr,
			[[maybe_unused]] std::size_t a_size,
			[[maybe_unused]] std::size_t a_alignment) { return false; }                              // 08
		[[nodiscard]] virtual std::size_t GetBase() const { return 0; }                                            // 09
		[[nodiscard]] virtual std::size_t GetSize() const { return 0; }                                            // 0A
		[[nodiscard]] virtual std::size_t GetFootprint() const { return 0; }                                       // 0B
		[[nodiscard]] virtual std::size_t GetUsedSpace() const { return 0; }                                       // 0C
		virtual void        VisitMem([[maybe_unused]] GHeapMemVisitor* a_visitor) const { return; }  // 0D
		virtual void        VisitSegments(
				   [[maybe_unused]] GHeapSegVisitor* a_visitor,
				   [[maybe_unused]] std::size_t      a_catSeg,
				   [[maybe_unused]] std::size_t      a_catUnused) const { return; }  // 0E
	};
	static_assert(sizeof(GSysAllocPaged) == 0x8);
}

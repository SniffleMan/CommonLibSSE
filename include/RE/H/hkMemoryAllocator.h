#pragma once

#include "RE/H/hkBaseTypes.h"

namespace RE
{
	class hkMemoryAllocator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkMemoryAllocator;

		using MemoryWalkCallback = void(void* a_start, std::size_t a_size, bool a_allocated, std::int32_t a_pool, void* a_param);

		enum class MemoryState
		{
			kOK,
			kOutOfMemory
		};

		struct MemoryStatistics
		{
		public:
			static constexpr std::int64_t INFINITE_SIZE = -1;

			// members
			std::int64_t allocated;       // 00
			std::int64_t inUse;           // 08
			std::int64_t peakInUse;       // 10
			std::int64_t available;       // 18
			std::int64_t totalAvailable;  // 20
			std::int64_t largestBlock;    // 28
		};
		static_assert(sizeof(MemoryStatistics) == 0x30);

		struct ExtendedInterface
		{
		public:
			virtual ~ExtendedInterface();  // 00

			// add
			virtual void        GarbageCollect() = 0;                                           // 01
			virtual void        IncrementalGarbageCollect(std::int32_t a_numBlocks) = 0;        // 02
			virtual hkResult    SetMemorySoftLimit(std::size_t a_maxMemory) = 0;                // 03
			[[nodiscard]] virtual std::size_t GetMemorySoftLimit() const = 0;                                 // 04
			virtual bool        CanAllocTotal(std::int32_t a_numBytes) = 0;                     // 05
			virtual hkResult    WalkMemory(MemoryWalkCallback* a_callback, void* a_param) = 0;  // 06
		};
		static_assert(sizeof(ExtendedInterface) == 0x8);

		virtual ~hkMemoryAllocator();  // 00

		// add
		virtual void*        BlockAlloc(std::int32_t a_numBytes) = 0;                                                   // 01
		virtual void         BlockFree(void* a_ptr, std::int32_t a_numBytes) = 0;                                       // 02
		virtual void*        BufAlloc(std::int32_t& a_reqNumBytesInOut);                                                // 03
		virtual void         BufFree(void* a_ptr, std::int32_t a_numBytes);                                             // 04
		virtual void*        BufRealloc(void* a_ptrOld, std::int32_t a_oldNumBytes, std::int32_t& a_reqNumBytesInOut);  // 05
		virtual void         BlockAllocBatch(void** a_ptrsOut, std::int32_t a_numPtrs, std::int32_t a_blockSize);       // 06
		virtual void         BlockFreeBatch(void** a_ptrsIn, std::int32_t a_numPtrs, std::int32_t a_blockSize);         // 07
		virtual void         GetMemoryStatistics(MemoryStatistics& a_usage) = 0;                                        // 08
		virtual std::int32_t GetAllocatedSize(const void* a_obj, std::int32_t a_numBytes) = 0;                          // 09
		virtual void         ResetPeakMemoryStatistics();                                                               // 0A - { return; }
	};
	static_assert(sizeof(hkMemoryAllocator) == 0x8);
}

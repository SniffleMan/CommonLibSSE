#pragma once

#include "RE/H/hkMemoryAllocator.h"
#include "RE/I/IMemoryHeap.h"

namespace RE
{
	class HeapBlock;
	class HeapBlockFreeHead;

	class bhkThreadMemorySource :
		public hkMemoryAllocator,  // 00
		public IMemoryHeap         // 08
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkThreadMemorySource;

		struct FreeBlock
		{
		public:
			// members
			FreeBlock* next;  // 0
		};
		static_assert(sizeof(FreeBlock) == 0x8);

		struct BlockPage
		{
		public:
			// members
			BlockPage*    left;       // 00
			BlockPage*    right;      // 08
			FreeBlock*    blocks;     // 10
			std::uint16_t totalElem;  // 18
			std::uint16_t freeElem;   // 1A
			std::uint32_t pad1C;      // 1C
		};
		static_assert(sizeof(BlockPage) == 0x20);

		struct Row
		{
		public:
			// members
			BlockPage*   pageList;              // 00
			BlockPage*   currAlloc;             // 08
			std::int32_t totalFreeBlocks;       // 10
			std::int32_t totalAllocatedBlocks;  // 14
			std::int32_t totalBytes;            // 18
			std::int32_t elemSize;              // 1C
		};
		static_assert(sizeof(Row) == 0x20);

		struct MegaBlockPage
		{
		public:
			// members
			char           mem[sizeof(BlockPage[255]) * 256];  // 000000
			BlockPage      blockPages[255];                    // 1FE000
			MegaBlockPage* left;                               // 1FFFE0
			MegaBlockPage* right;                              // 1FFFE8
			BlockPage*     freeBlockPages;                     // 1FFFF0
			std::uint16_t  numFreeBlockPages;                  // 1FFFF8
			std::uint16_t  nextBlockPageAlloc;                 // 1FFFFA
			bool           decommitted;                        // 1FFFFC
			std::uint8_t   pad1FFFFD;                          // 1FFFFD
			std::uint16_t  pad1FFFFE;                          // 1FFFFE
		};
		static_assert(sizeof(MegaBlockPage) == 0x200000);

		~bhkThreadMemorySource() override;  // 00

		// override (hkMemoryAllocator)
		void*        BlockAlloc(std::int32_t a_numBytes) override;                                                       // 01
		void         BlockFree(void* a_ptr, std::int32_t a_numBytes) override;                                           // 02
		void*        BufAlloc(std::int32_t& a_reqNumBytesInOut) override;                                                // 03
		void         BufFree(void* a_ptr, std::int32_t a_numBytes) override;                                             // 04
		void*        BufRealloc(void* a_ptrOld, std::int32_t a_oldNumBytes, std::int32_t& a_reqNumBytesInOut) override;  // 05
		void         BlockAllocBatch(void** a_ptrsOut, std::int32_t a_numPtrs, std::int32_t a_blockSize) override;       // 06
		void         BlockFreeBatch(void** a_ptrsIn, std::int32_t a_numPtrs, std::int32_t a_blockSize) override;         // 07
		void         GetMemoryStatistics(MemoryStatistics& a_usage) override;                                            // 08
		std::int32_t GetAllocatedSize(const void* a_obj, std::int32_t a_numBytes) override;                              // 09

		// override (IMemoryHeap)
		std::size_t   Size(const void* a_block) const override;                                      // 01
		void          GetMemoryStats(MemoryStats* a_stats) override;                                 // 02
		const char*   GetName() const override;                                                      // 07 - { return "bhkThreadMemorySource"; }
		void*         Allocate(std::size_t a_size, std::uint32_t a_alignment) override;              // 08
		void          Deallocate(void* a_pointer, std::uint32_t) override;                           // 09
		bool          PointerInHeap(const void* a_pointer) const override;                           // 0A
		std::size_t   TotalSize(const void* a_pointer) const override;                               // 0B
		void          GetHeapStats(HeapStats* a_stats, bool a_fullBlockInfo) override;               // 0C
		bool          ShouldTrySmallBlockPools(std::size_t a_size, MEM_CONTEXT a_context) override;  // 0D
		[[nodiscard]] std::uint32_t GetPageSize() const override;                                                  // 0E

		// members
		BSCriticalSection  lock;                    // 10
		Row*               rows;                    // 38
		std::uint16_t*     smallRowIndexes;         // 40
		std::uint16_t*     largeRowIndexes;         // 48
		HeapBlock**        lists;                   // 50
		HeapBlockFreeHead* largeFreeTrees;          // 58
		HeapBlock*         firstBlock;              // 60
		HeapBlock*         lastBlock;               // 68
		void*              memoryRoot;              // 70
		char*              allocBase;               // 78
		char*              blockStart;              // 80
		char*              allocEnd;                // 88
		char*              commitEnd;               // 90
		char*              blockPageCommit;         // 98
		char*              addressSpaceEnd;         // A0
		MegaBlockPage*     megaBlockPageList;       // A8
		MegaBlockPage*     currMegaBlockPageAlloc;  // B0
		std::int32_t       addressSpaceSize;        // B8
		std::int32_t       totalFreeBlockPages;     // BC
		std::uint32_t      usedRows;                // C0
		std::int32_t       totalAllocated;          // C4
		std::int32_t       totalFreeBlocks;         // C8
		std::int32_t       totalBlocks;             // CC
		bool               allowDecommits;          // D0
		std::uint8_t       padD1;                   // D1
		std::uint16_t      padD2;                   // D2
		std::uint32_t      padD4;                   // D4
	};
	static_assert(sizeof(bhkThreadMemorySource) == 0xD8);
}

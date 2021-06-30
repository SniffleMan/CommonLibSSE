#pragma once

#include "RE/E/ErrorCodes.h"
#include "RE/M/MemoryManager.h"

namespace RE
{
	namespace BSResource
	{
		struct Info;

		class StreamBase
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSResource__StreamBase;

			enum : std::uint32_t
			{
				kWritable = 1 << 0,
				kRefCountBeg = 0x1000,
				kRefCountMask = (std::uint32_t)0xFFFFF000
			};

			StreamBase();
			StreamBase(const StreamBase& a_rhs);
			StreamBase(StreamBase&& a_rhs);
			StreamBase(std::uint32_t a_totalSize);
			virtual ~StreamBase() = default;  // 00

			// add
			virtual ErrorCode     DoOpen() = 0;             // 01
			virtual void          DoClose() = 0;            // 02
			[[nodiscard]] virtual std::uint64_t DoGetKey() const;         // 03 - { return 0; }
			virtual ErrorCode     DoGetInfo(Info& a_info);  // 04 - { return ErrorCode::kUnsupported; }

			TES_HEAP_REDEFINE_NEW();

			std::uint32_t DecRef();
			std::uint32_t IncRef();
			[[nodiscard]] bool          IsWritable() const;

			// members
			std::uint32_t totalSize;  // 08
			std::uint32_t flags;      // 0C
		};
		static_assert(sizeof(StreamBase) == 0x10);
	}
}

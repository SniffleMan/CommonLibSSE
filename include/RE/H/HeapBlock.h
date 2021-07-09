#pragma once

namespace RE
{
	class HeapBlock
	{
	public:
		struct Free
		{
		public:
			// members
			HeapBlock* prevFree;  // 0
		};
		static_assert(sizeof(Free) == 0x8);

		struct Used
		{
		public:
			[[nodiscard]] std::uint32_t GetCheckPoint() const;
			[[nodiscard]] std::uint32_t GetMemContext() const;
			[[nodiscard]] std::uint32_t GetStackTrace() const;

			// members
			bool memContext1: 1;   // 0 - 0
			bool memContext2: 1;   // 0 - 1
			bool memContext3: 1;   // 0 - 2
			bool memContext4: 1;   // 0 - 3
			bool memContext5: 1;   // 0 - 4
			bool memContext6: 1;   // 0 - 5
			bool memContext7: 1;   // 0 - 6
			bool memContext8: 1;   // 0 - 7
			bool stackTrace1: 1;   // 1 - 0
			bool stackTrace2: 1;   // 1 - 1
			bool stackTrace3: 1;   // 1 - 2
			bool stackTrace4: 1;   // 1 - 3
			bool stackTrace5: 1;   // 1 - 4
			bool stackTrace6: 1;   // 1 - 5
			bool stackTrace7: 1;   // 1 - 6
			bool stackTrace8: 1;   // 1 - 7
			bool stackTrace9: 1;   // 2 - 0
			bool stackTrace10: 1;  // 2 - 1
			bool stackTrace11: 1;  // 2 - 2
			bool stackTrace12: 1;  // 2 - 3
			bool stackTrace13: 1;  // 2 - 4
			bool stackTrace14: 1;  // 2 - 5
			bool stackTrace15: 1;  // 2 - 6
			bool stackTrace16: 1;  // 2 - 7
			bool stackTrace17: 1;  // 3 - 0
			bool stackTrace18: 1;  // 3 - 1
			bool stackTrace19: 1;  // 3 - 2
			bool stackTrace20: 1;  // 3 - 3
			bool stackTrace21: 1;  // 3 - 4
			bool stackTrace22: 1;  // 3 - 5
			bool checkPoint1: 1;   // 3 - 6
			bool checkPoint2: 1;   // 3 - 7
		};
		static_assert(sizeof(Used) == 0x4);

		union FreeOrUsed
		{
			Free free;
			Used used;
		};
		static_assert(sizeof(FreeOrUsed) == 0x8);

		// members
		std::size_t memSize;     // 00
		HeapBlock*  previous;    // 08
		FreeOrUsed  freeOrUsed;  // 10
		HeapBlock*  nextFree;    // 18
	};
	static_assert(sizeof(HeapBlock) == 0x20);
}

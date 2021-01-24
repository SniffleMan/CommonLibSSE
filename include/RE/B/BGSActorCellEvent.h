#pragma once

namespace RE
{
	// related to cell transitions, trigger everytime when actor enter a new cell \ leave from a previous cell.
	struct BGSActorCellEvent
	{
		enum class CellFlag : std::uint32_t
		{
			kFlags_Enter = 0,
			kFlags_Leave = 1
		};

		ActorHandle     refHandle;
		FormID			cellID;
		CellFlag	    flags;
	};
	static_assert(sizeof(BGSActorCellEvent) == 0xc);
}

#pragma once

#include "RE/F/FormTypes.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESModelTextureSwap.h"

namespace RE
{
	struct TESObjectSTATData  // DNAM
	{
	public:
		enum class Flag
		{
			kNone = 0
		};

		// members
		float                                 materialThresholdAngle;  // 00 - (30 - 120)
		std::uint32_t                         pad04;                   // 04
		BGSMaterialObject*                    materialObj;             // 08
		stl::enumeration<Flag, std::uint32_t> flags;                   // 10
		std::uint32_t                         pad14;                   // 14
	};
	static_assert(sizeof(TESObjectSTATData) == 0x18);

	class TESObjectSTAT :
		public TESBoundObject,      // 00
		public TESModelTextureSwap  // 30
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESObjectSTAT;
		inline static constexpr auto FORMTYPE = FormType::Static;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kNeverFades = 1 << 2,
				kDeleted = 1 << 5,
				kHasTreeLOD = 1 << 6,
				kAddOnLODObject = 1 << 7,
				kHiddenFromLocalMap = 1 << 9,
				kHasDistantLOD = 1 << 15,
				kUsesHDLODTexture = 1 << 17,
				kHasCurrents = 1 << 19,
				kIsMarker = 1 << 23,
				kObstacle = 1 << 25,
				kNavMeshGeneration_Filter = 1 << 26,
				kNavMeshGeneration_BoundingBox = 1 << 27,
				kShowInWorldMap = 1 << 28,
				kNavMeshGeneration_Ground = 1 << 30
			};
		};

		~TESObjectSTAT() override;  // 00

		// override (TESBoundObject)
		void ClearData() override;              // 05
		bool Load(TESFile* a_mod) override;     // 06
		void InitItemImpl() override;           // 13
		bool GetPlayable() const override;      // 19 - { return true; }
		[[nodiscard]] bool IsHeadingMarker() const override;  // 1A - { return (flags >> 2) & 1; }

		[[nodiscard]] bool HasTreeLOD() const;

		// members
		TESObjectSTATData data;  // 68 - DNAM
	};
	static_assert(sizeof(TESObjectSTAT) == 0x80);
}

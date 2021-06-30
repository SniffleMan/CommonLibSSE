#pragma once

#include "RE/B/BGSDestructibleObjectForm.h"
#include "RE/B/BGSKeywordForm.h"
#include "RE/B/BGSMessageIcon.h"
#include "RE/B/BGSPickupPutdownSounds.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESIcon.h"
#include "RE/T/TESModelTextureSwap.h"
#include "RE/T/TESValueForm.h"
#include "RE/T/TESWeightForm.h"

namespace RE
{
	class TESObjectMISC :
		public TESBoundObject,             // 000
		public TESFullName,                // 030
		public TESModelTextureSwap,        // 040
		public TESIcon,                    // 078
		public TESValueForm,               // 088
		public TESWeightForm,              // 098
		public BGSDestructibleObjectForm,  // 0A8
		public BGSMessageIcon,             // 0B8
		public BGSPickupPutdownSounds,     // 0D0
		public BGSKeywordForm              // 0E8
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESObjectMISC;
		inline static constexpr auto FORMTYPE = FormType::Misc;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~TESObjectMISC() override;  // 00

		// override (TESBoundObject)
		bool Load(TESFile* a_mod) override;                // 06
		void SaveGame(BGSSaveFormBuffer* a_buf) override;  // 0E
		void LoadGame(BGSLoadFormBuffer* a_buf) override;  // 0F
		void InitItemImpl() override;                      // 13

		// override (BGSKeywordForm)
		[[nodiscard]] BGSKeyword* GetDefaultKeyword() const override;  // 05

		// add
		virtual void SaveImpl();                                         // 53 - { return; }
		virtual void LoadImpl(TESFile* a_mod, std::uint32_t a_chunkID);  // 54 - { return; }
		virtual void InitImpl();                                         // 55 - { return; }
	};
	static_assert(sizeof(TESObjectMISC) == 0x100);
}

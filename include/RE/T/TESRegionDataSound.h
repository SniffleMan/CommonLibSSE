#pragma once

#include "RE/B/BSTArray.h"
#include "RE/T/TESRegionData.h"

namespace RE
{
	class BGSMusicType;
	class BGSSoundDescriptorForm;
	class TESFile;

	class TESRegionDataSound : public TESRegionData
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESRegionDataSound;
		inline static constexpr auto TYPE = Type::kSound;

		struct Sound
		{
			enum class Flag
			{
				kNone = 0,
				kPleasant = 1 << 0,
				kCloudy = 1 << 1,
				kRainy = 1 << 2,
				kSnowy = 1 << 3
			};

			BGSSoundDescriptorForm*               sound;   // 00
			stl::enumeration<Flag, std::uint32_t> flags;   // 08
			float                                 chance;  // 0C
		};
		static_assert(sizeof(Sound) == 0x10);

		~TESRegionDataSound() override;  // 00

		// override (TESRegionData)
		void LoadData(TESForm* a_form) override;                    // 02
		Type GetType() const override;                              // 03 - { return Type::kSound; }
		void ConstructSelf() override;                              // 04
		void Unk_05(void) override;                                 // 05
		void CopyFrom(TESRegionData* a_src, bool a_copy) override;  // 06
		[[nodiscard]] bool IsLoaded() const override;                             // 07 - { return music == 0; }

		// add
		virtual void Load(TESFile* a_mod);  // 08

		// members
		BGSMusicType*    music;   // 10 - RDMO
		BSTArray<Sound*> sounds;  // 18 - RDSA
	};
	static_assert(sizeof(TESRegionDataSound) == 0x30);
}

#pragma once

#include "RE/B/BSISoundCategory.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"

namespace RE
{
	class BGSSoundCategory :
		public TESForm,          // 00
		public TESFullName,      // 20
		public BSISoundCategory  // 30
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSSoundCategory;
		inline static constexpr auto FORMTYPE = FormType::SoundCategory;

		enum class Flag  // FNAM
		{
			kNone = 0,
			kMuteWhenSubmerged = 1 << 0,
			kShouldAppearOnMenu = 1 << 1
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~BGSSoundCategory() override;  // 00

		// override (TESForm)
		void InitializeData() override;      // 04
		bool Load(TESFile* a_mod) override;  // 06
		void InitItemImpl() override;        // 13

		// override (BGSSoundCategory)
		bool          Matches(const BSISoundCategory* a_category) const override;  // 01
		float         GetCategoryVolume() const override;                          // 02
		void          SetCategoryVolume(float a_value) override;                   // 03
		float         GetCategoryFrequency() const override;                       // 04
		void          SetCategoryFrequency(float a_value) override;                // 05
		std::uint16_t GetCategoryAttenuation() const override;                     // 06
		void          SetCategoryAttenuation(std::uint16_t a_value) override;      // 07

		[[nodiscard]] float GetDefaultMenuValue() const;
		[[nodiscard]] float GetStaticVolumeMultiplier() const;
		[[nodiscard]] bool  IsMenuCategory() const;
		void  SetDefaultMenuValue(float a_val);
		void  SetStaticVolumeMultiplier(float a_val);

		// members
		stl::enumeration<Flag, std::uint32_t> flags;             // 38 - FNAM
		std::uint32_t                         unk3C;             // 3C
		BGSSoundCategory*                     parentCategory;    // 40 - SNCT
		std::uint16_t                         unk48;             // 48
		std::uint16_t                         attenuation;       // 4A
		std::uint16_t                         staticMult;        // 4C - VNAM
		std::uint16_t                         defaultMenuValue;  // 4E - UNAM
		float                                 volumeMult;        // 50
		float                                 frequencyMult;     // 54
	};
	static_assert(sizeof(BGSSoundCategory) == 0x58);
}

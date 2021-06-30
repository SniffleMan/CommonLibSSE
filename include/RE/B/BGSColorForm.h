#pragma once

#include "RE/C/Color.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"

namespace RE
{
	class BGSColorForm :
		public TESForm,     // 00
		public TESFullName  // 20
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSColorForm;
		inline static constexpr auto FORMTYPE = FormType::ColorForm;

		enum class Flag  // FNAM
		{
			kNone = 0,
			kPlayable = 1 << 0
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~BGSColorForm() override;  // 00

		// override (TESForm)
		void InitializeData() override;      // 04
		void ClearData() override;           // 05
		bool Load(TESFile* a_mod) override;  // 06

		[[nodiscard]] bool IsPlayable() const;

		// memebrs
		Color                                 color;  // 30 - CNAM
		stl::enumeration<Flag, std::uint32_t> flags;  // 34 - FNAM
	};
	static_assert(sizeof(BGSColorForm) == 0x38);
}

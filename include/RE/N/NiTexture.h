#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/N/NiObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	NiSmartPointer(NiTexture);

	class NiTexture : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTexture;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiTexture;

		class FormatPrefs
		{
		public:
			enum class PixelLayout
			{
				kPalettized8,
				kHighColor16,
				kTrueColor32,
				kCompressed,
				kBumpmap,
				kPalettized4,
				kDefault,
				kSingleColor8,
				kSingleColor16,
				kSingleColor32,
				kDoubleColor32,
				kDoubleColor64,
				kFloatColor32,
				kFloatColor64,
				kFloatColor128
			};

			enum class AlphaFormat
			{
				kNone,
				kBinary,  // 1-bit
				kSmooth,  // multi-bit
				kDefault
			};

			enum class MipFlag
			{
				kNo = 0,
				kYes = 1,
				kDefault
			};

			FormatPrefs();

			// members
			stl::enumeration<PixelLayout, std::uint32_t> pixelLayout;  // 00
			stl::enumeration<AlphaFormat, std::uint32_t> alphaFormat;  // 04
			stl::enumeration<MipFlag, std::uint32_t>     mipMapped;    // 08
			std::uint32_t                                pad0C;        // 0C
		};
		static_assert(sizeof(FormatPrefs) == 0x10);

		~NiTexture() override;

		// override (NiObject)
		[[nodiscard]] const NiRTTI* GetRTTI() const override;  // 02

		// add
		virtual void Unk_25(void);  // 25 - { return 0; }
		virtual void Unk_26(void);  // 26 - { return 0; }
		virtual void Unk_27(void);  // 27 - { return "n/a"; }
		virtual void Unk_28(void);  // 28
		virtual void Unk_29(void);  // 29 - { return 0; }
		virtual void Unk_2A(void);  // 2A - { return 0; }

		// members
		FormatPrefs   formatPrefs;  // 10
		BSFixedString name;         // 20
		std::uint32_t unk28;        // 28
		std::uint32_t unk2C;        // 2C
		NiTexture*    prev;         // 30
		NiTexture*    next;         // 38
	};
	static_assert(sizeof(NiTexture) == 0x40);
}

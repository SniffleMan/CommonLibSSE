#pragma once

namespace RE
{
	class GFxResourceID
	{
	public:
		struct IDTypeConstants
		{
			enum IDTypeConstant : std::uint32_t
			{
				kIndexMask = 0x0000FFFF,
				kTypeMask = 0x0FFF0000,
				kGenMask = 0x00030000,

				kSWF = 0,
				kStatic = 1 << 12,
				kExport = 1 << 13,

				kTypeShift = 18,

				kInvalidID = (1 << kTypeShift) | kSWF
			};
		};

		struct IDTypes
		{
			enum IDType : std::uint32_t
			{
				kNone = IDTypeConstants::kSWF,
				kInternalConstant = (0 << IDTypeConstants::kTypeShift) | IDTypeConstants::kStatic,
				kGradientImage = (1 << IDTypeConstants::kTypeShift) | IDTypeConstants::kStatic,
				kDynFontImage = (2 << IDTypeConstants::kTypeShift) | IDTypeConstants::kStatic,
				kFontImage = (1 << IDTypeConstants::kTypeShift) | IDTypeConstants::kStatic
			};
		};

		class HashOp
		{
		public:
			UPInt operator()(const GFxResourceID& a_idRef);
		};

		GFxResourceID();
		explicit GFxResourceID(std::uint32_t a_resID);
		GFxResourceID(const GFxResourceID& a_rhs);

		GFxResourceID& operator=(const GFxResourceID& a_rhs);
		bool           operator==(const GFxResourceID& a_rhs) const;
		bool           operator!=(const GFxResourceID& a_rhs) const;
		bool           operator==(std::uint32_t a_idVal) const;
		bool           operator!=(std::uint32_t a_idVal) const;

		[[nodiscard]] std::uint32_t   GetIDValue() const;
		[[nodiscard]] std::uint32_t   GetIDIndex() const;
		[[nodiscard]] IDTypes::IDType GetIDType() const;
		GFxResourceID   GenerateNextID();

	protected:
		// members
		std::uint32_t id;  // 0
	};
	static_assert(sizeof(GFxResourceID) == 0x4);
}
